# Task LED Vibe Lamp - 鑷祴鎿嶄綔鎵嬪唽

## 浜у搧姒傝堪

杩欐槸涓€娆惧熀浜嶦SP8266鐨勬櫤鑳芥皼鍥寸伅锛岃兘鏍规嵁Codex AI缂栫▼鍔╂墜鐨勫伐浣滅姸鎬佽嚜鍔ㄥ彉鎹㈤鑹层€?鐢ㄦ埛鍦ㄧ數鑴戜笂涓嶤odex瀵硅瘽鏃讹紝鐏甫浼氬疄鏃跺弽鏄燗I鐨勫伐浣滈樁娈点€?
---

## 浜у搧鍔熻兘妯″潡鎬昏

### 妯″潡1锛歐iFi閰嶇綉妯″潡 (Captive Portal)

| 椤圭洰 | 璇存槑 |
|------|------|
| 鍔熻兘 | 棣栨浣跨敤鏃堕厤缃甒iFi杩炴帴 |
| 鎶€鏈?| ESP8266 AP妯″紡 + DNS寮哄埗闂ㄦ埛 |
| AP鍚嶇О | Task-LED-Setup |
| AP鍦板潃 | 192.168.4.1 |
| 瑙﹀彂鏉′欢 | 鏃犱繚瀛樺嚟璇?/ 鍑瘉杩炴帴澶辫触 |
| 鐢ㄦ埛鎿嶄綔 | 鎵嬫満杩濧P 鈫?鑷姩寮瑰嚭椤甸潰 鈫?杈撳叆WiFi淇℃伅 鈫?鎻愪氦 |

### 妯″潡2锛歐iFi杩炴帴绠＄悊妯″潡

| 椤圭洰 | 璇存槑 |
|------|------|
| 鍔熻兘 | 鑷姩杩炴帴宸蹭繚瀛樼殑WiFi |
| 瀛樺偍 | EEPROM (鍦板潃98-101瀛榤agic, 0-97瀛樺嚟璇? |
| 閲嶈繛 | 鏂嚎鑷姩閲嶅惎骞堕噸杩?|
| 閲嶉厤 | 杩炴帴澶辫触鑷姩娓呴櫎鍑瘉锛岄噸鏂拌繘鍏ラ厤缃戞ā寮?|

### 妯″潡3锛氫簯绔湇鍔″櫒妯″潡 (Serv00)

| 椤圭洰 | 璇存槑 |
|------|------|
| 鍦板潃 | s11.serv00.com:13470 |
| 鍔熻兘 | 鎺ユ敹PC鎸囦护锛屽瓨鍌ㄥ綋鍓嶉鑹茬姸鎬侊紝渚汦SP8266鏌ヨ |
| 鎺ュ彛 | POST /update_status (PC鍙戞寚浠? |
| 鎺ュ彛 | GET /get_status (ESP8266鏌ラ鑹? |
| 鎺ュ彛 | POST /set_idle (鍏崇伅) |
| 鎺ュ彛 | GET /health (鍋ュ悍妫€鏌? |

### 妯″潡4锛歅C鎺у埗鑴氭湰妯″潡

| 椤圭洰 | 璇存槑 |
|------|------|
| 鏂囦欢 | D:\zhuanqian\danpianji\codex_lamp_cloud.py |
| 鍔熻兘 | 鏍规嵁Codex宸ヤ綔闃舵鍙戦€侀鑹叉寚浠ゅ埌浜戠 |
| 璋冪敤 | python codex_lamp_cloud.py <闃舵> "娑堟伅" |
| 闆嗘垚 | AGENTS.md閰嶇疆锛孋odex鑷姩璋冪敤 |

### 妯″潡5锛欵SP8266鍥轰欢妯″潡

| 椤圭洰 | 璇存槑 |
|------|------|
| 鏂囦欢 | D:\zhuanqian\danpianji\TaskLED_Cloud\TaskLED_Cloud.ino |
| 鍔熻兘 | 杩炴帴WiFi 鈫?杞浜戠 鈫?鎺у埗LED棰滆壊 |
| 杞 | 姣?绉掓煡璇竴娆′簯绔姸鎬?|
| 涓插彛 | COM6, 115200娉㈢壒鐜?|

### 妯″潡6锛歀ED鐏甫鎺у埗妯″潡

| 椤圭洰 | 璇存槑 |
|------|------|
| 鐏甫 | WS2812B, 30棰桳ED |
| 寮曡剼 | GPIO2 (D4) |
| 浜害 | 80/255 |
| 棰滆壊 | 4绉?+ 鐏伅 |

### 妯″潡7锛歄LED鏄剧ず妯″潡

| 椤圭洰 | 璇存槑 |
|------|------|
| 灞忓箷 | SSD1306, 0.96瀵? 128x64 |
| 杩炴帴 | I2C (SDA=GPIO12/D6, SCL=GPIO14/D5) |
| 鍦板潃 | 0x3C (澶囬€?x3D) |
| 鏄剧ず | 褰撳墠IP鍦板潃銆佸伐浣滄ā寮忋€丩ED鐘舵€?|

---

## 棰滆壊瀹氫箟

| 闃舵 | 棰滆壊 | RGB鍊?| 鍚箟 |
|------|------|-------|------|
| thinking | 钃濊壊 | 0, 0, 255 | AI鍦ㄦ€濊€?瑙勫垝 |
| working | 绱壊 | 180, 0, 255 | AI鍦ㄧ紪鐮?鎵ц |
| success | 缁胯壊 | 0, 255, 0 | 浠诲姟瀹屾垚 |
| error | 绾㈣壊 | 255, 0, 0 | 浠诲姟澶辫触 |
| idle | 鐏伅 | 0, 0, 0 | 寰呮満/鏃犱换鍔?|

---

## 鑷祴娴佺▼

### 娴嬭瘯0锛氱幆澧冨噯澶?
**纭欢娓呭崟锛?*
- ESP8266 0.96 OLED闆嗘垚鏉?x1
- WS2812B LED鐏甫 x1 (30棰?
- USB鏁版嵁绾?x1
- 鐢垫簮 (USB渚涚數)

**鎺ョ嚎纭锛?*
- LED鐏甫 GND 鈫?鏉垮瓙 GND
- LED鐏甫 VCC 鈫?鏉垮瓙 5V (鎴朧U)
- LED鐏甫 DATA 鈫?鏉垮瓙 D4 (GPIO2)
- OLED灞忓箷 鈫?宸查泦鎴愬湪鏉垮瓙涓?(SDA=D6, SCL=D5)

**杞欢娓呭崟锛?*
- Arduino CLI: D:\zhuanqian\danpianji\arduino-cli\arduino-cli.exe
- Python 3.x
- 涓插彛宸ュ叿 (鍙敤Python鑴氭湰鏇夸唬)
- 鎵嬫満 (鐢ㄤ簬WiFi閰嶇綉)

---

### 娴嬭瘯1锛氬浐浠剁紪璇戝拰涓婁紶

**鐩爣锛?* 楠岃瘉鍥轰欢鑳芥纭紪璇戝苟鐑у綍鍒癊SP8266

**姝ラ锛?*

```powershell
# 1. 缂栬瘧鍥轰欢
D:\zhuanqian\danpianji\arduino-cli\arduino-cli.exe compile --fqbn esp8266:esp8266:nodemcuv2 D:\zhuanqian\danpianji\TaskLED_Cloud\TaskLED_Cloud.ino

# 2. 涓婁紶鍥轰欢 (纭繚COM6姝ｇ‘)
D:\zhuanqian\danpianji\arduino-cli\arduino-cli.exe upload --fqbn esp8266:esp8266:nodemcuv2 -p COM6 D:\zhuanqian\danpianji\TaskLED_Cloud\TaskLED_Cloud.ino
```

**棰勬湡缁撴灉锛?*
- 缂栬瘧鎴愬姛锛屾樉绀哄唴瀛樹娇鐢ㄧ巼 (RAM绾?8%, Flash绾?9%)
- 涓婁紶鎴愬姛锛屾樉绀?"Hash of data verified"

**閫氳繃鏍囧噯锛?* 鏃犳姤閿欙紝涓婁紶瀹屾垚

---

### 娴嬭瘯2锛氶娆″惎鍔ㄥ拰閰嶇綉妯″紡

**鐩爣锛?* 楠岃瘉ESP8266棣栨鍚姩杩涘叆AP閰嶇綉妯″紡

**姝ラ锛?*

1. 涓婁紶鍥轰欢鍚庯紝ESP8266鑷姩閲嶅惎
2. 绛夊緟10绉?3. 鐢ㄦ墜鏈烘悳绱iFi锛屾壘鍒?"Task-LED-Setup"
4. 杩炴帴璇iFi

**涓插彛楠岃瘉 (鍙€?锛?*

```powershell
python -c "
import serial, sys, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ser = serial.Serial('COM6', 115200, timeout=2)
time.sleep(20)
data = ser.read(65536)
print(data.decode('utf-8', errors='replace'))
ser.close()
"
```

**棰勬湡涓插彛杈撳嚭锛?*
```
=== Task LED v4 (EEPROM Fix) ===
[OLED] Display OK
[EEPROM] Magic check: FAIL
[Boot] No credentials. Starting portal...
[AP] Started: Task-LED-Setup @ 192.168.4.1
[DNS] Captive portal active
[Portal] Ready! Connect phone to 'Task-LED-Setup'
```

**閫氳繃鏍囧噯锛?*
- 鎵嬫満鑳芥悳鍒?"Task-LED-Setup" WiFi
- OLED灞忓箷鏄剧ず "WiFi Setup Mode" 鍜?"Task-LED Setup" 瀛楁牱
- 涓插彛鏄剧ず "No credentials. Starting portal..."

---

### 娴嬭瘯3锛欳aptive Portal閰嶇綉

**鐩爣锛?* 楠岃瘉鎵嬫満杩炴帴AP鍚庤兘鑷姩寮瑰嚭閰嶇綉椤甸潰骞舵垚鍔熶繚瀛榃iFi淇℃伅

**姝ラ锛?*

1. 鎵嬫満杩炴帴 "Task-LED-Setup" WiFi
2. 鎵嬫満搴旇嚜鍔ㄥ脊鍑洪厤缃戦〉闈?(濡傛湭寮瑰嚭锛屾墜鍔ㄦ墦寮€娴忚鍣ㄨ闂?192.168.4.1)
3. 鍦ㄩ〉闈腑杈撳叆锛?   - WiFi鍚嶇О锛氫綘瀹剁殑WiFi鍚?(濡?lihongxing)
   - WiFi瀵嗙爜锛氫綘瀹剁殑WiFi瀵嗙爜 (濡?lihongxing)
4. 鐐瑰嚮 "Connect" 鎸夐挳
5. 绛夊緟椤甸潰鏄剧ず "Saved Successfully!"

**涓插彛楠岃瘉锛?*

```powershell
python -c "
import serial, sys, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ser = serial.Serial('COM6', 115200, timeout=2)
time.sleep(30)
data = ser.read(65536)
print(data.decode('utf-8', errors='replace'))
ser.close()
"
```

**棰勬湡涓插彛杈撳嚭锛?*
```
[Save] Args: 2
  [0] 'ssid' = 'lihongxing'
  [1] 'pass' = 'lihongxing'
[Save] Saving: ssid='lihongxing' pass='lihongxing'
[EEPROM] SAVED & VERIFY: magic=OK ssid_len=10 pass_len=10
[Save] Testing connection...
[WiFi] Connecting to 'lihongxing' (pass len=10)
[WiFi] status=7
[WiFi] status=7
[WiFi] Connected! IP: 192.168.1.xxx
[Save] Connected! IP: 192.168.1.xxx
```

**閫氳繃鏍囧噯锛?*
- 椤甸潰鏄剧ず "Saved Successfully!"
- 涓插彛鏄剧ず "SAVED & VERIFY: magic=OK"
- 涓插彛鏄剧ず "Connected! IP: 192.168.1.xxx"
- LED缁胯壊闂儊涓€娆?
**澶辫触澶勭悊锛?*
- 濡傛灉涓插彛鏄剧ず "magic=FAIL" 鈫?EEPROM鍐欏叆寮傚父锛岄渶妫€鏌ュ浐浠剁増鏈?- 濡傛灉涓插彛鏄剧ず "Failed (status=X)" 鈫?WiFi瀵嗙爜閿欒鎴栦俊鍙峰急
- 濡傛灉鎵嬫満娌″脊鍑洪〉闈?鈫?鎵嬪姩鎵撳紑娴忚鍣ㄨ闂?192.168.4.1

---

### 娴嬭瘯4锛歐iFi鑷姩閲嶈繛

**鐩爣锛?* 楠岃瘉ESP8266閲嶅惎鍚庤兘鑷姩杩炴帴宸蹭繚瀛樼殑WiFi

**姝ラ锛?*

1. 鎷旀帀ESP8266鐨刄SB绾?2. 绛夊緟5绉?3. 閲嶆柊鎻掑叆USB绾?4. 绛夊緟30绉?
**涓插彛楠岃瘉锛?*

```powershell
python -c "
import serial, sys, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
ser = serial.Serial('COM6', 115200, timeout=2)
time.sleep(25)
data = ser.read(65536)
print(data.decode('utf-8', errors='replace'))
ser.close()
"
```

**棰勬湡涓插彛杈撳嚭锛?*
```
=== Task LED v4 (EEPROM Fix) ===
[OLED] Display OK
[EEPROM] Magic check: OK
[EEPROM] Loaded: ssid='lihongxing' pass='lihongxing' (len=10)
[Boot] Found saved WiFi: 'lihongxing'
[WiFi] Connecting to 'lihongxing' (pass len=10)
[WiFi] Connected! IP: 192.168.1.xxx
[Boot] Setup done, entering loop
```

**閫氳繃鏍囧噯锛?*
- 涓插彛鏄剧ず "Magic check: OK"
- 涓插彛鏄剧ず "Loaded: ssid='lihongxing'"
- 涓插彛鏄剧ず "Connected! IP: 192.168.1.xxx"
- 涓嶅啀杩涘叆AP閰嶇綉妯″紡
- OLED灞忓箷鏄剧ずIP鍦板潃

---

### 娴嬭瘯5锛氫簯绔湇鍔″櫒鍋ュ悍妫€鏌?
**鐩爣锛?* 楠岃瘉Serv00浜戞湇鍔″櫒姝ｅ父杩愯

**姝ラ锛?*

```powershell
# 鍋ュ悍妫€鏌?python -c "import requests; r=requests.get('http://s11.serv00.com:13470/health', timeout=10, proxies={'http':None,'https':None}); print(r.status_code, r.text)"

# 鏌ョ湅褰撳墠鐘舵€?python -c "import requests; r=requests.get('http://s11.serv00.com:13470/get_status', timeout=10, proxies={'http':None,'https':None}); print(r.status_code, r.text)"
```

**棰勬湡缁撴灉锛?*
- health杩斿洖: `200 {"ok": true}`
- get_status杩斿洖: `200 {"r":0, "g":0, "b":0, "status":"idle"}`

**閫氳繃鏍囧噯锛?* 涓や釜鎺ュ彛閮借繑鍥?00鐘舵€佺爜

---

### 娴嬭瘯6锛歅C鑴氭湰鍙戦€佹寚浠?
**鐩爣锛?* 楠岃瘉PC鑴氭湰鑳芥垚鍔熷彂閫侀鑹叉寚浠ゅ埌浜戠

**姝ラ锛?*

```powershell
# 鍙戦€乼hinking (钃濊壊)
python D:\zhuanqian\danpianji\codex_lamp_cloud.py thinking "Test blue"

# 鍙戦€乻uccess (缁胯壊)
python D:\zhuanqian\danpianji\codex_lamp_cloud.py success "Test green"

# 鍙戦€乪rror (绾㈣壊)
python D:\zhuanqian\danpianji\codex_lamp_cloud.py error "Test red"

# 鍙戦€亀orking (绱壊)
python D:\zhuanqian\danpianji\codex_lamp_cloud.py working "Test purple"

# 鍏崇伅 (idle)
python D:\zhuanqian\danpianji\codex_lamp_cloud.py idle "Test off"
```

**棰勬湡缁撴灉锛?*
- 姣忎釜鍛戒护閮借繑鍥?`"ok": true`
- 鏃犱唬鐞嗚秴鏃堕敊璇?
**閫氳繃鏍囧噯锛?* 鎵€鏈夊懡浠よ繑鍥炴垚鍔燂紝鏃犲紓甯?
---

### 娴嬭瘯7锛歀ED鐏甫棰滆壊鍝嶅簲

**鐩爣锛?* 楠岃瘉ESP8266鑳戒粠浜戠鑾峰彇棰滆壊骞舵帶鍒禠ED鐏甫

**姝ラ锛?*

1. 纭繚ESP8266宸茶繛鎺iFi (娴嬭瘯4閫氳繃)
2. 杩愯浠ヤ笅鑴氭湰锛?
```powershell
python -c "
import serial, sys, time, threading
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
sys.path.insert(0, r'D:\zhuanqian\danpianji')
from codex_lamp_cloud import send_status, send_idle

ser = serial.Serial('COM6', 115200, timeout=2)

def send_commands():
    time.sleep(2)
    for status in ['error', 'success', 'working', 'thinking']:
        print(f'[PC] Sending {status}...')
        send_status(status)
        time.sleep(4)
    print('[PC] Sending idle...')
    send_idle()

t = threading.Thread(target=send_commands)
t.start()

start = time.time()
all_data = b''
while time.time() - start < 22:
    chunk = ser.read(4096)
    if chunk:
        all_data += chunk
t.join()

text = all_data.decode('utf-8', errors='replace')
print('=== ESP8266 Serial Output ===')
print(text if text.strip() else '(no output)')
ser.close()
"
```

**棰勬湡涓插彛杈撳嚭锛?*
```
[PC] Sending error...
[PC] Sending success...
[PC] Sending working...
[PC] Sending thinking...
[PC] Sending idle...
=== ESP8266 Serial Output ===
-> error (255,0,0)
-> success (0,255,0)
-> working (180,0,255)
-> thinking (0,0,255)
```

**閫氳繃鏍囧噯锛?*
- 涓插彛鏄剧ず4绉嶉鑹插彉鍖?- LED鐏甫瀹為檯棰滆壊涓庝覆鍙ｈ緭鍑轰竴鑷?- 鏈€鍚庣伅甯︾唲鐏?(idle)

**鑲夌溂妫€鏌ワ細**
- error 鈫?绾㈣壊浜捣
- success 鈫?鍙樹负缁胯壊
- working 鈫?鍙樹负绱壊
- thinking 鈫?鍙樹负钃濊壊
- idle 鈫?鐏伃

---

### 娴嬭瘯8锛歄LED灞忓箷鏄剧ず

**鐩爣锛?* 楠岃瘉OLED灞忓箷姝ｇ‘鏄剧ず淇℃伅

**姝ラ锛?*

1. ESP8266宸茶繛鎺iFi
2. 瑙傚療OLED灞忓箷

**棰勬湡鏄剧ず锛?*
- 绗?琛岋細IP: 192.168.1.xxx
- 绗?琛岋細Mode: thinking/working/success/error/idle
- 涓棿澶у瓧锛氬綋鍓嶆ā寮忓悕绉?- 搴曡锛歀ED: ON R,G,B 鎴?LED: OFF

**閫氳繃鏍囧噯锛?*
- 灞忓箷涓嶅叏榛?鍏ㄧ櫧
- 鑳界湅鍒癐P鍦板潃
- 妯″紡鍚嶇О闅忛鑹插懡浠ゅ彉鍖?
**鏁呴殰鎺掓煡锛?*
- 鍏ㄧ櫧 鈫?I2C鎺ョ嚎鍙嶄簡
- 鍏ㄩ粦 鈫?瀵规瘮搴﹂棶棰樻垨灞忓箷鏈垵濮嬪寲
- 涓嶆樉绀?鈫?妫€鏌DA(D6)鍜孲CL(D5)鎺ョ嚎

---

### 娴嬭瘯9锛欳odex鑷姩闆嗘垚

**鐩爣锛?* 楠岃瘉Codex AI鍔╂墜鑳借嚜鍔ㄦ帶鍒剁伅甯?
**姝ラ锛?*

1. 纭繚 AGENTS.md 鏂囦欢瀛樺湪浜庨」鐩洰褰?2. 鍦–odex涓彂璧蜂竴涓柊瀵硅瘽
3. 璁〤odex鎵ц涓€涓换鍔?(濡?"甯垜鍐欎竴涓狧ello World绋嬪簭")
4. 瑙傚療鐏甫棰滆壊鍙樺寲

**棰勬湡琛屼负锛?*
- Codex寮€濮嬫€濊€冩椂 鈫?鐏彉钃濊壊 (thinking)
- Codex寮€濮嬪啓浠ｇ爜鏃?鈫?鐏彉绱壊 (working)
- Codex瀹屾垚浠诲姟鏃?鈫?鐏彉缁胯壊 (success)
- 濡傛灉鍑洪敊 鈫?鐏彉绾㈣壊 (error)
- 瀵硅瘽缁撴潫鍚?鈫?鐏伃 (idle)

**閫氳繃鏍囧噯锛?* 鐏甫棰滆壊鍙樺寲涓嶤odex宸ヤ綔闃舵鍚屾

---

### 娴嬭瘯10锛氬畬鏁翠骇鍝佹祦绋嬫ā鎷?
**鐩爣锛?* 妯℃嫙鐪熷疄鐢ㄦ埛浠庡紑绠卞埌浣跨敤鐨勫畬鏁存祦绋?
**姝ラ锛?*

1. **寮€绠憋細** 灏咵SP8266鏉垮瓙閫氳繃USB杩炴帴鐢佃剳
2. **棣栨閰嶇綉锛?*
   - 鎵嬫満鎼滅储 "Task-LED-Setup" WiFi骞惰繛鎺?   - 鍦ㄥ脊鍑洪〉闈㈣緭鍏iFi淇℃伅
   - 鎻愪氦鍚庣瓑寰呰繛鎺ユ垚鍔?3. **楠岃瘉杩炴帴锛?*
   - 鎷旀帀USB锛岀瓑寰?绉掞紝閲嶆柊鎻掑叆
   - 纭ESP8266鑷姩杩炴帴WiFi (涓嶈繘鍏ラ厤缃戞ā寮?
4. **浣跨敤锛?*
   - 鍦ㄧ數鑴戜笂鎵撳紑Codex
   - 璁〤odex鎵ц浠诲姟
   - 瑙傚療鐏甫棰滆壊闅忓伐浣滈樁娈靛彉鍖?5. **寰呮満锛?*
   - 浠诲姟瀹屾垚鍚庣伅鑷姩鐔勭伃
   - 涓嬫浣跨敤鏃惰嚜鍔ㄥ搷搴?
**閫氳繃鏍囧噯锛?* 鏁翠釜娴佺▼鏃犻渶鎵嬪姩骞查锛岀伅甯﹁嚜鍔ㄥ搷搴?
---

## 鏁呴殰鎺掓煡閫熸煡琛?
### 闂1锛氭墜鏈烘悳涓嶅埌 "Task-LED-Setup" WiFi

**鍙兘鍘熷洜锛?*
- ESP8266鏈纭惎鍔?- 鍥轰欢鏈纭笂浼?
**瑙ｅ喅锛?*
- 閲嶆柊涓婁紶鍥轰欢 (娴嬭瘯1)
- 妫€鏌ヤ覆鍙ｈ緭鍑虹‘璁P宸插惎鍔?
---

### 闂2锛氳繛涓夾P浣嗕笉寮瑰嚭閰嶇綉椤甸潰

**鍙兘鍘熷洜锛?*
- 鎵嬫満Captive Portal妫€娴嬭绂佺敤
- DNS鏈嶅姟鍣ㄦ湭鍚姩

**瑙ｅ喅锛?*
- 鎵嬪姩鎵撳紑娴忚鍣ㄨ闂?192.168.4.1
- 妫€鏌ヤ覆鍙ｆ槸鍚︽樉绀?"DNS Captive portal active"

---

### 闂3锛氭彁浜iFi淇℃伅鍚庤繛鎺ュけ璐?
**鍙兘鍘熷洜锛?*
- WiFi瀵嗙爜閿欒
- WiFi淇″彿寮?- 璺敱鍣ㄤ笉鍏煎

**瑙ｅ喅锛?*
- 妫€鏌ヤ覆鍙ｆ棩蹇椾腑鐨勫瘑鐮侀暱搴﹀拰鍐呭
- 闈犺繎璺敱鍣ㄩ噸璇?- 纭WiFi鏄?.4GHz (ESP8266涓嶆敮鎸?GHz)

---

### 闂4锛氶噸鍚悗涓嶈嚜鍔ㄨ繛鎺iFi

**鍙兘鍘熷洜锛?*
- EEPROM淇濆瓨澶辫触 (magic鍊奸敊璇?

**瑙ｅ喅锛?*
- 妫€鏌ヤ覆鍙ｆ槸鍚︽樉绀?"Magic check: OK"
- 濡傛灉鏄剧ず "Magic check: FAIL"锛岄噸鏂颁笂浼犲浐浠跺苟閲嶆柊閰嶇綉

---

### 闂5锛歀ED鐏甫涓嶅彉鑹?
**鍙兘鍘熷洜锛?*
- ESP8266鏈繛鎺iFi
- 浜戠鏈嶅姟鍣ㄤ笉鍙揪
- LED鐏甫鎺ョ嚎閿欒

**瑙ｅ喅锛?*
- 妫€鏌ヤ覆鍙ｆ槸鍚︽樉绀?"Connected! IP: xxx"
- 杩愯娴嬭瘯5妫€鏌ヤ簯绔湇鍔″櫒
- 妫€鏌ED鐏甫DATA绾挎槸鍚︽帴D4 (GPIO2)

---

### 闂6锛歅C鑴氭湰鍙戦€佸け璐?
**鍙兘鍘熷洜锛?*
- 浠ｇ悊杞欢 (濡侳lClash) 鎷︽埅璇锋眰
- 缃戠粶涓嶉€?
**瑙ｅ喅锛?*
- 纭鑴氭湰浣跨敤浜?proxies={'http': None, 'https': None}
- 鎵嬪姩娴嬭瘯: python -c "import requests; r=requests.get('http://s11.serv00.com:13470/health', timeout=10, proxies={'http':None,'https':None}); print(r.text)"

---

### 闂7锛歄LED灞忓箷涓嶆樉绀?
**鍙兘鍘熷洜锛?*
- I2C鍦板潃涓嶅尮閰?- 鎺ョ嚎閿欒
- 灞忓箷纭欢鏁呴殰

**瑙ｅ喅锛?*
- 妫€鏌ヤ覆鍙ｆ槸鍚︽樉绀?"[OLED] Display OK"
- 纭SDA鎺6 (GPIO12), SCL鎺5 (GPIO14)
- 灏濊瘯鏇存崲灞忓箷

---

## 鏂囦欢娓呭崟

| 鏂囦欢 | 璺緞 | 鐢ㄩ€?|
|------|------|------|
| ESP8266鍥轰欢 | D:\zhuanqian\danpianji\TaskLED_Cloud\TaskLED_Cloud.ino | 鏉垮瓙杩愯鐨勭▼搴?|
| PC鎺у埗鑴氭湰 | D:\zhuanqian\danpianji\codex_lamp_cloud.py | 鍙戦€侀鑹叉寚浠?|
| 浜戠鏈嶅姟鍣?| D:\zhuanqian\danpianji\cloud\server.py | 涓浆鏈嶅姟鍣?|
| 椤圭洰閰嶇疆 | C:\Users\lee\Documents\New project\AGENTS.md | Codex鑷姩璋冪敤閰嶇疆 |

---

## 蹇€熸祴璇曞懡浠?
```powershell
# 涓€閿祴璇曞叏娴佺▼ (澶嶅埗绮樿创杩愯)
python -c "
import requests, time

# 1. 浜戠鍋ュ悍妫€鏌?r = requests.get('http://s11.serv00.com:13470/health', timeout=10, proxies={'http':None,'https':None})
print('1. Cloud health:', r.json())

# 2. 鍙戦€?绉嶉鑹?for status in ['thinking', 'working', 'success', 'error']:
    r = requests.post('http://s11.serv00.com:13470/update_status', json={'status': status}, timeout=10, proxies={'http':None,'https':None})
    print('2. Send', status, ': ok=', r.json().get('ok'))
    time.sleep(3)

# 3. Turn off
r = requests.post('http://s11.serv00.com:13470/set_idle', timeout=10, proxies={'http':None,'https':None})
print('3. Set idle:', r.json())
print('Done! Check if LED changed colors.')
"
```

---

## 鐗堟湰淇℃伅

- 鍥轰欢鐗堟湰: Task LED v4 (EEPROM Fix)
- EEPROM甯冨眬: magic@98, ssid@1-32, pass@34-97
- 浜戠鍦板潃: s11.serv00.com:13470
- 鏈€鍚庢洿鏂? 2026-06-07





