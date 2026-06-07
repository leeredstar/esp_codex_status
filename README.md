# Task LED - Codex Vibe Lamp

ESP8266 smart ambient lamp that changes color based on Codex AI coding assistant work status.

## Features

- **WiFi Auto-Provisioning** - Phone connects to AP, setup page pops up automatically
- **Cloud Control** - Commands routed through Serv00 server
- **4 Colors** - Blue (thinking), Purple (coding), Green (success), Red (error)
- **Standby White Light** - Dim white when idle, proves LED strip works
- **Factory Reset** - Hold FLASH button 3 seconds to reset WiFi

## Hardware Requirements

- ESP8266 board (NodeMCU v3 / D1 Mini)
- WS2812B LED strip (30 LEDs)
- USB cable

## Wiring

```
LED Strip GND  -> Board GND
LED Strip VCC  -> Board 5V (or VU)
LED Strip DATA -> Board D4 (GPIO2)
```

## Quick Start

### 1. Install Arduino CLI

```powershell
# Download Arduino CLI
# https://arduino.github.io/arduino-cli/latest/installation/

# Install ESP8266 platform
arduino-cli core install esp8266:esp8266

# Install required libraries
arduino-cli lib install "Adafruit NeoPixel"
arduino-cli lib install "ArduinoJson"
```

### 2. Compile Firmware

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 3. Upload Firmware

```powershell
# List serial ports
arduino-cli board list

# Upload (replace COM6 with your port)
arduino-cli upload --fqbn esp8266:esp8266:nodemcuv2 -p COM6 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 4. Configure WiFi

1. Plug in power, LED strip lights up white
2. Phone search WiFi: `Task-LED-Setup`
3. Connect and setup page pops up automatically
4. Enter WiFi name and password
5. Click Connect
6. Wait for green flash x5 = success

### 5. Install Codex Skill

```powershell
# Copy skill to Codex skills directory
Copy-Item -Recurse vibe-lamp-skill/vibe-lamp ~/.codex/skills/
```

## Project Structure

```
.
├── TaskLED_Cloud/
│   └── TaskLED_Cloud.ino    # ESP8266 firmware
├── codex_lamp_cloud.py      # PC controller script
├── cloud/
│   └── server.py            # Cloud server
├── vibe-lamp-skill/
│   └── vibe-lamp/
│       ├── SKILL.md         # Codex skill
│       └── agents/
│           └── openai.yaml  # Skill metadata
├── TEST_GUIDE.md            # Test documentation
└── README.md
```

## How It Works

```
Codex working -> PC script -> Cloud server -> ESP8266 polling -> LED color change
```

1. Codex performs tasks, automatically calls `codex_lamp_cloud.py`
2. Script sends HTTP POST to Serv00 server
3. ESP8266 polls server every 2 seconds for color
4. Receives color and controls LED strip

## Color Definition

| Status | Color | RGB |
|--------|-------|-----|
| thinking | Blue | 0, 0, 255 |
| working | Purple | 180, 0, 255 |
| success | Green | 0, 255, 0 |
| error | Red | 255, 0, 0 |
| standby | White (dim) | 20, 20, 20 |

## Factory Reset

**Method 1: Hardware Reset**
- Hold FLASH button 3 seconds
- Wait for red flash x5
- Auto-enters setup mode

**Method 2: Web Reset**
- Connect to `Task-LED-Setup` WiFi
- Visit `http://192.168.4.1/reset`
- Confirm reset

## Response Time

| Stage | Time |
|-------|------|
| PC -> Cloud | ~550ms |
| Cloud -> ESP8266 | ~4.7s |
| Total | ~5.3s |

## Troubleshooting

**Q: Can't find Task-LED-Setup WiFi**
A: Unplug and replug power, wait 10 seconds

**Q: Setup page won't open**
A: Manually visit `192.168.4.1` in browser

**Q: WiFi connection fails**
A: Make sure it's 2.4GHz network (ESP8266 doesn't support 5GHz)

**Q: LED strip not lighting**
A: Check wiring, DATA wire to D4 (GPIO2)

**Q: Colors not changing**
A: Check internet connection, verify cloud server is running

## Tech Stack

- ESP8266 (NodeMCU v3 / D1 Mini)
- Arduino CLI
- Adafruit NeoPixel
- ArduinoJson
- Flask (Python)
- Serv00 cloud server

## License

MIT License

## Author

leeredstar
