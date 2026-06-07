/*
 * Task LED v1 - With Factory Reset Button
 * 
 * New features:
 *   - Long press FLASH button (GPIO0) for 3 seconds = factory reset
 *   - LED feedback during reset (red flash)
 *   - OLED shows reset countdown
 *   - /reset endpoint in AP portal for web-based reset
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DNSServer.h>

#define LED_PIN   2
#define LED_COUNT 30
#define BRIGHTNESS 80
#define SDA_PIN   12
#define SCL_PIN   14
#define BTN_PIN   0    // FLASH button on GPIO0 (D3)
#define RESET_HOLD_MS 3000  // Hold 3 seconds to reset

const char* SERVER = "s11.serv00.com";
const int PORT = 13470;
const char* PATH = "/get_status";

// EEPROM layout (128 bytes total):
// [0]     = SSID length
// [1-32]  = SSID (max 32 chars)
// [33]    = PASS length
// [34-97] = PASS (max 64 chars)
// [98-101]= Magic (4 bytes: 0xEF, 0xBE, 0xAD, 0xDE)
#define EEPROM_SIZE 128
#define SSID_LEN    0
#define SSID_ADDR   1
#define PASS_LEN    33
#define PASS_ADDR   34
#define MAGIC_ADDR  98

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
bool hasDisplay = false;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
WiFiClient http_client;
ESP8266WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;

int curR=0, curG=0, curB=0;
String mode = "idle";
String ip = "...";
bool ledsOn = false;
bool inStandby = false;
unsigned long lastPoll = 0;
unsigned long lastDraw = 0;

// Button state
unsigned long btnPressStart = 0;
bool btnWasPressed = false;
bool resetTriggered = false;

// ===================== EEPROM =====================
bool checkMagic() {
  return EEPROM.read(MAGIC_ADDR)   == 0xEF &&
         EEPROM.read(MAGIC_ADDR+1) == 0xBE &&
         EEPROM.read(MAGIC_ADDR+2) == 0xAD &&
         EEPROM.read(MAGIC_ADDR+3) == 0xDE;
}

void writeMagic() {
  EEPROM.write(MAGIC_ADDR,   0xEF);
  EEPROM.write(MAGIC_ADDR+1, 0xBE);
  EEPROM.write(MAGIC_ADDR+2, 0xAD);
  EEPROM.write(MAGIC_ADDR+3, 0xDE);
}

void saveCredentials(String ssid, String pass) {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(SSID_LEN, (uint8_t)ssid.length());
  for (int i=0; i<32; i++) EEPROM.write(SSID_ADDR+i, i<(int)ssid.length() ? ssid[i] : 0);
  EEPROM.write(PASS_LEN, (uint8_t)pass.length());
  for (int i=0; i<64; i++) EEPROM.write(PASS_ADDR+i, i<(int)pass.length() ? pass[i] : 0);
  writeMagic();
  EEPROM.commit();
  bool ok = checkMagic();
  int vsl = EEPROM.read(SSID_LEN);
  int vpl = EEPROM.read(PASS_LEN);
  EEPROM.end();
  Serial.printf("[EEPROM] SAVED & VERIFY: magic=%s ssid_len=%d pass_len=%d\n", 
    ok ? "OK" : "FAIL", vsl, vpl);
}

bool loadCredentials(String &ssid, String &pass) {
  EEPROM.begin(EEPROM_SIZE);
  bool magicOk = checkMagic();
  Serial.printf("[EEPROM] Magic check: %s\n", magicOk ? "OK" : "FAIL");
  if (!magicOk) {
    EEPROM.end();
    return false;
  }
  int sl = EEPROM.read(SSID_LEN);
  int pl = EEPROM.read(PASS_LEN);
  if (sl <= 0 || sl > 32 || pl > 64) {
    EEPROM.end();
    return false;
  }
  ssid = ""; pass = "";
  for (int i=0; i<sl; i++) ssid += (char)EEPROM.read(SSID_ADDR+i);
  for (int i=0; i<pl; i++) pass += (char)EEPROM.read(PASS_ADDR+i);
  EEPROM.end();
  Serial.printf("[EEPROM] Loaded: ssid='%s' (pass len=%d)\n", ssid.c_str(), pl);
  return true;
}

void clearCredentials() {
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(MAGIC_ADDR, 0);
  EEPROM.commit();
  EEPROM.end();
  Serial.println("[EEPROM] Cleared (magic invalidated)");
}

// ===================== Display =====================
void initDisplay() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);
  hasDisplay = oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (!hasDisplay) hasDisplay = oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  if (hasDisplay) {
    oled.ssd1306_command(SSD1306_SETCONTRAST);
    oled.ssd1306_command(0xFF);
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("Task LED v1");
    oled.println("Booting...");
    oled.display();
    Serial.println("[OLED] Display OK");
  } else {
    Serial.println("[OLED] Display NOT found");
  }
}

void drawScreen() {
  if (!hasDisplay) return;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print("IP: ");
  oled.println(ip);
  oled.setCursor(0, 12);
  oled.print("Mode: ");
  oled.println(mode);
  oled.setCursor(0, 28);
  oled.setTextSize(2);
  oled.println(mode);
  oled.setTextSize(1);
  oled.setCursor(0, 52);
  oled.print(ledsOn ? "LED: ON" : "LED: OFF");
  if (ledsOn) {
    oled.print(" ");
    oled.print(curR); oled.print(",");
    oled.print(curG); oled.print(",");
    oled.print(curB);
  }
  oled.display();
}

void drawAPScreen() {
  if (!hasDisplay) return;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("WiFi Setup Mode");
  oled.println();
  oled.println("Connect to WiFi:");
  oled.setTextSize(2);
  oled.setCursor(0, 24);
  oled.println("Task-LED");
  oled.println("Setup");
  oled.setTextSize(1);
  oled.setCursor(0, 54);
  oled.println("Then open any webpage");
  oled.display();
}

void drawConnectingScreen(String ssid) {
  if (!hasDisplay) return;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("Connecting...");
  oled.println();
  oled.print("SSID: ");
  oled.println(ssid);
  oled.println();
  oled.println("Please wait...");
  oled.display();
}

void drawResetScreen(int secondsLeft) {
  if (!hasDisplay) return;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("!!! FACTORY RESET !!!");
  oled.println();
  oled.print("Hold button for ");
  oled.print(secondsLeft);
  oled.println("s");
  oled.println();
  oled.println("Release to cancel");
  oled.setTextSize(2);
  oled.setCursor(0, 40);
  oled.print("  ");
  oled.print(secondsLeft);
  oled.println("s");
  oled.display();
}

void drawResetDone() {
  if (!hasDisplay) return;
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("WiFi Cleared!");
  oled.println();
  oled.println("Restarting into");
  oled.println("setup mode...");
  oled.display();
}

// ===================== LEDs =====================
void ledsOnColor(int r, int g, int b) {
  curR=r; curG=g; curB=b; ledsOn=true; inStandby=false;
  for (int i=0; i<LED_COUNT; i++) strip.setPixelColor(i, strip.Color(r,g,b));
  strip.show();
}

void ledsOff() {
  if (!ledsOn) return;
  curR=curG=curB=0; ledsOn=false;
  for (int i=0; i<LED_COUNT; i++) strip.setPixelColor(i, 0);
  strip.show();
}

void blinkMulti(int r, int g, int b, int onMs, int offMs, int count) {
  for (int i=0; i<count; i++) {
    ledsOnColor(r,g,b); delay(onMs);
    ledsOff(); delay(offMs);
  }
}

void ledsDimWhite() {
  // Dim white standby light
  for (int i=0; i<LED_COUNT; i++) strip.setPixelColor(i, strip.Color(20, 20, 20));
  strip.show();
  ledsOn = false;
  inStandby = true;
}

void blink(int r, int g, int b, int ms) {
  ledsOnColor(r,g,b); delay(ms); ledsOff(); delay(100);
}

// ===================== Cloud =====================
void pollCloud() {
  if (WiFi.status() != WL_CONNECTED) return;
  HTTPClient http;
  String url = String("http://") + SERVER + ":" + PORT + PATH;
  http.begin(http_client, url);
  http.setTimeout(3000);
  int code = http.GET();
  if (code == 200) {
    String payload = http.getString();
    JsonDocument doc;
    if (!deserializeJson(doc, payload)) {
      int r = doc["r"] | -1;
      int g = doc["g"] | -1;
      int b = doc["b"] | -1;
      String newMode = doc["status"] | "?";
      if (r==0 && g==0 && b==0) {
        if (ledsOn || !inStandby) { ledsDimWhite(); mode = "standby"; Serial.println("-> STANDBY (dim white)"); }
      } else if (r>=0 && g>=0 && b>=0) {
        if (r!=curR || g!=curG || b!=curB || newMode != mode) {
          ledsOnColor(r,g,b);
          mode = newMode;
          Serial.printf("-> %s (%d,%d,%d)\n", mode.c_str(), r, g, b);
        }
      }
    }
  }
  http.end();
}

// ===================== Factory Reset =====================
void doFactoryReset() {
  Serial.println("[RESET] Factory reset triggered!");
  
  // Visual feedback: rapid red blink
  for (int i=0; i<5; i++) {
    ledsOnColor(255, 0, 0);
    delay(100);
    ledsOff();
    delay(100);
  }
  
  drawResetDone();
  clearCredentials();
  
  // Also clear cloud status to idle
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String("http://") + SERVER + ":" + PORT + "/set_idle";
    http.begin(http_client, url);
    http.setTimeout(2000);
    http.POST("");
    http.end();
  }
  
  delay(1000);
  ESP.restart();
}

void checkResetButton() {
  bool pressed = (digitalRead(BTN_PIN) == LOW); // Active LOW
  
  if (pressed && !btnWasPressed) {
    // Button just pressed
    btnPressStart = millis();
    btnWasPressed = true;
  }
  
  if (pressed && btnWasPressed) {
    unsigned long heldMs = millis() - btnPressStart;
    int remaining = (RESET_HOLD_MS - heldMs) / 1000 + 1;
    if (remaining < 1) remaining = 1;
    
    // Show countdown on screen after 1 second of holding
    if (heldMs > 1000) {
      drawResetScreen(remaining);
      // Blink orange during countdown
      if ((heldMs / 200) % 2 == 0) {
        ledsOnColor(255, 128, 0);
      } else {
        ledsOff();
      }
    }
    
    // Trigger reset after hold time
    if (heldMs >= RESET_HOLD_MS) {
      resetTriggered = true;
      doFactoryReset();
    }
  }
  
  if (!pressed && btnWasPressed) {
    // Button released (before reset threshold)
    btnWasPressed = false;
    ledsOff(); // Turn off countdown LED
    Serial.printf("[BTN] Released after %lu ms (need %d ms to reset)\n", 
      millis() - btnPressStart, RESET_HOLD_MS);
  }
}

// ===================== HTML Pages =====================
const char portalHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset='utf-8'>
<meta name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1'>
<title>Task LED Setup</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
body{font-family:-apple-system,system-ui,sans-serif;background:#f0f4f8;min-height:100vh;display:flex;align-items:center;justify-content:center;padding:20px}
.card{background:#fff;border-radius:16px;box-shadow:0 4px 24px rgba(0,0,0,0.1);padding:32px 28px;max-width:380px;width:100%}
.icon{text-align:center;font-size:48px;margin-bottom:8px}
h1{text-align:center;font-size:20px;font-weight:600;color:#1a1a2e;margin-bottom:4px}
.sub{text-align:center;font-size:13px;color:#888;margin-bottom:24px}
label{font-size:13px;font-weight:500;color:#555;display:block;margin:16px 0 6px}
input{width:100%;padding:14px 16px;border:1.5px solid #e0e0e0;border-radius:12px;font-size:15px}
input:focus{outline:none;border-color:#6366f1;box-shadow:0 0 0 3px rgba(99,102,241,0.1)}
.btn{width:100%;background:linear-gradient(135deg,#6366f1,#8b5cf6);color:#fff;padding:16px;border:none;border-radius:12px;font-size:16px;font-weight:600;margin-top:24px;cursor:pointer}
.btn:active{transform:scale(0.98)}
.hint{text-align:center;margin-top:16px;font-size:12px;color:#aaa}
.danger{margin-top:32px;padding-top:24px;border-top:1px solid #eee;text-align:center}
.danger a{color:#e74c3c;font-size:13px;text-decoration:none}
.danger a:hover{text-decoration:underline}
</style></head><body>
<div class="card">
<div class="icon">&#128161;</div>
<h1>Task LED Setup</h1>
<p class="sub">Connect your lamp to WiFi</p>
<form method='POST' action='/save'>
<label>WiFi Name</label>
<input name='ssid' placeholder='Enter WiFi name' required autocomplete='off' autocapitalize='off' spellcheck='false'>
<label>WiFi Password</label>
<input name='pass' type='password' placeholder='Enter password'>
<button class='btn' type='submit'>Connect</button>
</form>
<p class="hint">After saving, the lamp will restart and connect automatically.</p>
<div class="danger">
<p style="font-size:12px;color:#999;margin-bottom:8px">Having trouble? You can also:</p>
<a href="/reset">Factory Reset (clear WiFi settings)</a>
</div>
</div>
</body></html>)rawliteral";

const char savedHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset='utf-8'>
<meta name='viewport' content='width=device-width,initial-scale=1'>
<style>
body{font-family:-apple-system,system-ui,sans-serif;display:flex;align-items:center;justify-content:center;min-height:100vh;background:#f0f4f8;margin:0}
.card{background:#fff;border-radius:16px;box-shadow:0 4px 24px rgba(0,0,0,0.1);padding:48px 32px;text-align:center;max-width:320px}
.check{font-size:72px;margin-bottom:12px}
h2{font-size:20px;color:#1a1a2e;margin-bottom:8px}
p{font-size:14px;color:#888;line-height:1.6}
</style></head><body>
<div class="card">
<div class="check">&#10004;</div>
<h2>Saved Successfully!</h2>
<p>The lamp is now connecting to your WiFi.<br><br>
If it fails, the setup network will reappear.<br>
You can close this page now.</p>
</div>
</body></html>)rawliteral";

const char resetConfirmHTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset='utf-8'>
<meta name='viewport' content='width=device-width,initial-scale=1'>
<style>
body{font-family:-apple-system,system-ui,sans-serif;display:flex;align-items:center;justify-content:center;min-height:100vh;background:#f0f4f8;margin:0}
.card{background:#fff;border-radius:16px;box-shadow:0 4px 24px rgba(0,0,0,0.1);padding:48px 32px;text-align:center;max-width:320px}
.warn{font-size:72px;margin-bottom:12px}
h2{font-size:20px;color:#e74c3c;margin-bottom:8px}
p{font-size:14px;color:#888;line-height:1.6;margin-bottom:24px}
.btn{background:#e74c3c;color:#fff;padding:14px 32px;border:none;border-radius:10px;font-size:16px;font-weight:600;cursor:pointer;margin:0 8px}
.btn2{background:#ccc;color:#333;padding:14px 32px;border:none;border-radius:10px;font-size:16px;cursor:pointer;margin:0 8px}
</style></head><body>
<div class="card">
<div class="warn">&#9888;</div>
<h2>Factory Reset</h2>
<p>This will erase all WiFi settings.<br>The lamp will restart in setup mode.</p>
<form method='POST' action='/reset_confirm'>
<button class='btn2' type='button' onclick='history.back()'>Cancel</button>
<button class='btn' type='submit'>Reset</button>
</form>
</div>
</body></html>)rawliteral";

// ===================== Portal Handlers =====================
void handleRoot() {
  server.send(200, "text/html", portalHTML);
}

void handleDebug() {
  EEPROM.begin(EEPROM_SIZE);
  bool magicOk = checkMagic();
  int sl = EEPROM.read(SSID_LEN);
  int pl = EEPROM.read(PASS_LEN);
  String ssid = "", pass = "";
  for (int i=0; i<sl && i<32; i++) ssid += (char)EEPROM.read(SSID_ADDR+i);
  for (int i=0; i<pl && i<64; i++) pass += (char)EEPROM.read(PASS_ADDR+i);
  EEPROM.end();
  
  String dbg = "EEPROM:\r\n";
  dbg += "  Magic: " + String(magicOk ? "OK" : "NONE") + "\r\n";
  dbg += "  SSID: '" + ssid + "'\r\n";
  dbg += "  PASS: '" + pass + "'\r\n";
  dbg += "\r\nWiFi: " + String(WiFi.status()==WL_CONNECTED ? "Connected" : "Not connected") + "\r\n";
  dbg += "IP: " + WiFi.localIP().toString() + "\r\n";
  dbg += "\r\nButton: " + String(digitalRead(BTN_PIN)==LOW ? "PRESSED" : "released") + "\r\n";
  server.send(200, "text/plain", dbg);
}

void handleResetPage() {
  server.send(200, "text/html", resetConfirmHTML);
}

void handleResetConfirm() {
  Serial.println("[Web] Factory reset via web!");
  server.send(200, "text/html", "<html><body style='text-align:center;padding:60px'><h1>Resetting...</h1><p>WiFi cleared. Lamp restarting.</p></body></html>");
  delay(2000);
  doFactoryReset();
}

void handleSave() {
  Serial.printf("[Save] Args: %d\n", server.args());
  for (int i=0; i<server.args(); i++) {
    Serial.printf("  [%d] '%s' = '%s'\n", i, server.argName(i).c_str(), server.arg(i).c_str());
  }
  
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");
  
  if (ssid.length() == 0) {
    server.send(400, "text/plain", "Error: WiFi name required");
    return;
  }
  
  Serial.printf("[Save] Saving: ssid='%s' pass='%s'\n", ssid.c_str(), pass.c_str());
  saveCredentials(ssid, pass);
  server.send(200, "text/html", savedHTML);
  delay(3000);
  
  Serial.println("[Save] Testing connection...");
  drawConnectingScreen(ssid);
  
  // Full WiFi reset before connecting
  WiFi.softAPdisconnect(true);  // Turn off AP
  WiFi.disconnect(true);         // Disconnect STA
  WiFi.mode(WIFI_OFF);           // Turn off WiFi completely
  delay(1000);
  WiFi.mode(WIFI_STA);           // Turn on in station mode
  WiFi.setOutputPower(20.0);     // Max power
  delay(500);
  WiFi.begin(ssid.c_str(), pass.c_str());
  
  int att = 0;
  while (WiFi.status() != WL_CONNECTED && att < 30) {
    delay(500);
    int st = WiFi.status();
    Serial.printf("[Save] attempt %d status=%d\n", att, st);
    att++;
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("[Save] Connected! IP: %s\n", WiFi.localIP().toString().c_str());
    blinkMulti(0, 255, 0, 300, 200, 5); // 5x green flash = success
  } else {
    Serial.printf("[Save] Failed (status=%d)\n", WiFi.status());
    blinkMulti(255, 0, 0, 300, 200, 5); // 5x red flash = fail
  }
  ESP.restart();
}

void handleCaptivePortal() {
  server.sendHeader("Location", String("http://192.168.4.1/"), true);
  server.send(302, "text/plain", "");
}

void handleGenerate204() {
  server.sendHeader("Location", String("http://192.168.4.1/"), true);
  server.send(302, "text/plain", "");
}

void handleHotspotDetect() {
  server.sendHeader("Location", String("http://192.168.4.1/"), true);
  server.send(302, "text/plain", "");
}

// ===================== AP Portal =====================
void startPortal() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Task-LED-Setup");
  delay(500);
  IPAddress apIP = WiFi.softAPIP();
  Serial.printf("[AP] Started: Task-LED-Setup @ %s\n", apIP.toString().c_str());
  
  drawAPScreen();
  
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.println("[DNS] Captive portal active");
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/debug", HTTP_GET, handleDebug);
  server.on("/reset", HTTP_GET, handleResetPage);
  server.on("/reset_confirm", HTTP_POST, handleResetConfirm);
  server.on("/generate_204", handleGenerate204);
  server.on("/gen_204", handleGenerate204);
  server.on("/hotspot-detect.html", handleHotspotDetect);
  server.on("/library/test/success.html", handleHotspotDetect);
  server.on("/connecttest.txt", handleCaptivePortal);
  server.on("/ncsi.txt", handleCaptivePortal);
  server.on("/success.txt", handleCaptivePortal);
  server.onNotFound(handleCaptivePortal);
  
  server.begin();
  Serial.println("[Portal] Ready! Connect phone to 'Task-LED-Setup'");
  
  while (true) {
    dnsServer.processNextRequest();
    server.handleClient();
    checkResetButton(); // Allow hardware reset in AP mode too
    yield();
  }
}

// ===================== Connect =====================
bool tryConnect(String ssid, String pass, int timeoutSec) {
  Serial.printf("[WiFi] Connecting to '%s' (pass len=%d)\n", ssid.c_str(), pass.length());
  drawConnectingScreen(ssid);
  
  // Full WiFi reset
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.setOutputPower(20.0);
  WiFi.persistent(false);
  delay(500);
  WiFi.begin(ssid.c_str(), pass.c_str());
  
  int att = 0;
  int maxAtt = timeoutSec * 2;
  while (WiFi.status() != WL_CONNECTED && att < maxAtt) {
    delay(500);
    int st = WiFi.status();
    if (att % 2 == 0) Serial.printf("[WiFi] attempt %d status=%d\n", att, st);
    att++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    ip = WiFi.localIP().toString();
    Serial.printf("[WiFi] Connected! IP: %s\n", ip.c_str());
    return true;
  }
  Serial.printf("[WiFi] Failed! status=%d\n", WiFi.status());
  return false;
}

// ===================== Setup =====================
void setup() {
  Serial.begin(115200);
  Serial.println("\n================================");
  Serial.println("=== Task LED v1 (WiFi Fix) ===");
  Serial.println("================================");
  
  // Init button pin (internal pull-up, active LOW)
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.println("[BTN] Flash button ready (GPIO0, hold 3s to reset)");
  
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  ledsOff();
  initDisplay();
  
  String ssid, pass;
  bool hasCreds = loadCredentials(ssid, pass);
  
  if (hasCreds) {
    Serial.printf("[Boot] Found saved WiFi: '%s'\n", ssid.c_str());
    if (tryConnect(ssid, pass, 20)) {
      if (hasDisplay) {
        oled.clearDisplay();
        oled.setCursor(0, 0);
        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);
        oled.println("WiFi Connected!");
        oled.println();
        oled.print("IP: ");
        oled.println(ip);
        oled.println();
        oled.println("Ready!");
        oled.println();
        oled.println("Hold FLASH 3s = Reset");
        oled.display();
      }
      blink(0, 80, 0, 500);
      delay(500);
      ledsDimWhite(); // Show white standby light
      delay(2000);
    } else {
      Serial.println("[Boot] Failed! Clearing & starting portal...");
      clearCredentials();
      startPortal();
    }
  } else {
    Serial.println("[Boot] No credentials. Starting portal...");
    startPortal();
  }
  Serial.println("[Boot] Setup done, entering loop");
}

// ===================== Loop =====================
void loop() {
  unsigned long now = millis();
  
  // Check reset button every loop
  checkResetButton();
  
  if (now - lastPoll >= 2000) {
    lastPoll = now;
    pollCloud();
  }
  if (now - lastDraw >= 500) {
    lastDraw = now;
    drawScreen();
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Lost! Restarting...");
    delay(1000);
    ESP.restart();
  }
  yield();
}





