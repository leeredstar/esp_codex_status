# Task LED - Codex Vibe Lamp

ESP8266 鏅鸿兘姘涘洿鐏紝鏍规嵁 Codex AI 缂栫▼鍔╂墜鐨勫伐浣滅姸鎬佽嚜鍔ㄥ彉鎹㈤鑹层€?
## 鍔熻兘鐗圭偣

- **WiFi 鑷姩閰嶇綉** - 鎵嬫満杩炴帴 AP 鑷姩寮瑰嚭璁剧疆椤甸潰
- **浜戠鎺у埗** - 閫氳繃 Serv00 鏈嶅姟鍣ㄤ腑杞寚浠?- **4 绉嶉鑹?* - 钃濊壊(鎬濊€?銆佺传鑹?缂栫爜)銆佺豢鑹?鎴愬姛)銆佺孩鑹?閿欒)
- **寰呮満鐧界伅** - 绌洪棽鏃跺井浜櫧鑹诧紝璇佹槑鐏甫姝ｅ父
- **闀挎寜閲嶇疆** - FLASH 鎸夐挳 3 绉掓仮澶嶅嚭鍘傝缃?- **OLED 鏄剧ず** - 鏄剧ず IP 鍦板潃鍜屽綋鍓嶇姸鎬?
## 纭欢闇€姹?
- ESP8266 0.96 OLED 闆嗘垚鏉?- WS2812B LED 鐏甫 (30棰?
- USB 鏁版嵁绾?
## 鎺ョ嚎鏂瑰紡

```
LED鐏甫 GND  鈫?鏉垮瓙 GND
LED鐏甫 VCC  鈫?鏉垮瓙 5V (鎴?VU)
LED鐏甫 DATA 鈫?鏉垮瓙 D4 (GPIO2)
OLED 灞忓箷    鈫?宸查泦鎴?(SDA=D6, SCL=D5)
```

## 蹇€熷紑濮?
### 1. 瀹夎 Arduino CLI

```powershell
# 涓嬭浇 Arduino CLI
# https://arduino.github.io/arduino-cli/latest/installation/

# 瀹夎 ESP8266 骞冲彴
arduino-cli core install esp8266:esp8266

# 瀹夎鎵€闇€搴?arduino-cli lib install "Adafruit NeoPixel"
arduino-cli lib install "Adafruit SSD1306"
arduino-cli lib install "ArduinoJson"
```

### 2. 缂栬瘧鍥轰欢

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 3. 涓婁紶鍥轰欢

```powershell
# 鏌ョ湅涓插彛
arduino-cli board list

# 涓婁紶 (鏇挎崲 COM3 涓轰綘鐨勪覆鍙?
arduino-cli upload --fqbn esp8266:esp8266:nodemcuv2 -p COM6 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 4. 閰嶇疆 WiFi

1. 鎻掍笂鐢垫簮锛岀伅甯︿寒鐧借壊
2. 鎵嬫満鎼滅储 WiFi锛歚Task-LED-Setup`
3. 杩炴帴鍚庤嚜鍔ㄥ脊鍑鸿缃〉闈?4. 杈撳叆 WiFi 鍚嶇О鍜屽瘑鐮?5. 鐐瑰嚮 Connect
6. 绛夊緟缁跨伅闂?5 涓?= 閰嶇疆鎴愬姛

### 5. 閮ㄧ讲浜戠鏈嶅姟鍣?
```powershell
# 鐧诲綍 Serv00 鏈嶅姟鍣?ssh billgatesxing11@s11.serv00.com -p 22

# 涓婁紶 server.py
scp -P 22 cloud/server.py billgatesxing11@s11.serv00.com:~/

# 瀹夎渚濊禆
pip install flask

# 杩愯鏈嶅姟鍣?(鍚庡彴)
nohup python server.py > server.log 2>&1 &
```

### 6. 瀹夎 Codex 鎶€鑳?
```powershell
# 澶嶅埗鎶€鑳藉埌 Codex 鎶€鑳界洰褰?Copy-Item -Recurse vibe-lamp-skill/vibe-lamp ~/.codex/skills/
```

## 椤圭洰缁撴瀯

```
.
鈹溾攢鈹€ TaskLED_Cloud/
鈹?  鈹斺攢鈹€ TaskLED_Cloud.ino    # ESP8266 鍥轰欢
鈹溾攢鈹€ codex_lamp_cloud.py      # PC 鎺у埗鑴氭湰
鈹溾攢鈹€ cloud/
鈹?  鈹斺攢鈹€ server.py            # 浜戠鏈嶅姟鍣?鈹溾攢鈹€ vibe-lamp-skill/
鈹?  鈹斺攢鈹€ vibe-lamp/
鈹?      鈹斺攢鈹€ SKILL.md         # Codex 鎶€鑳?鈹溾攢鈹€ TEST_GUIDE.md            # 鑷祴鏂囨。
鈹斺攢鈹€ README.md
```

## 宸ヤ綔鍘熺悊

```
Codex 宸ヤ綔 鈫?PC 鑴氭湰 鈫?浜戠鏈嶅姟鍣?鈫?ESP8266 杞 鈫?LED 鍙樿壊
```

1. Codex 鎵ц浠诲姟鏃讹紝鑷姩璋冪敤 `codex_lamp_cloud.py`
2. 鑴氭湰鍙戦€?HTTP POST 鍒?Serv00 鏈嶅姟鍣?3. ESP8266 姣?2 绉掕疆璇㈡湇鍔″櫒鑾峰彇棰滆壊
4. 鏀跺埌棰滆壊鍚庢帶鍒?LED 鐏甫鍙樿壊

## 棰滆壊瀹氫箟

| 鐘舵€?| 棰滆壊 | RGB |
|------|------|-----|
| thinking | 钃濊壊 | 0, 0, 255 |
| working | 绱壊 | 180, 0, 255 |
| success | 缁胯壊 | 0, 255, 0 |
| error | 绾㈣壊 | 255, 0, 0 |
| standby | 鐧借壊 (寰寒) | 20, 20, 20 |

## 鎭㈠鍑哄巶璁剧疆

**鏂规硶 1锛氱‖浠堕噸缃?*
- 闀挎寜 FLASH 鎸夐挳 3 绉?- 绛夊緟绾㈢伅闂?5 涓?- 鑷姩杩涘叆閰嶇綉妯″紡

**鏂规硶 2锛氱綉椤甸噸缃?*
- 杩炴帴 `Task-LED-Setup` WiFi
- 璁块棶 `http://192.168.4.1/reset`
- 纭閲嶇疆

## 鍝嶅簲鏃堕棿

| 鐜妭 | 鑰楁椂 |
|------|------|
| PC 鈫?浜戠 | ~550ms |
| 浜戠 鈫?ESP8266 | ~4.7s |
| 鎬昏 | ~5.3s |

## 鏁呴殰鎺掓煡

**Q: 鎵嬫満鎼滀笉鍒?Task-LED-Setup WiFi**
A: 鎷旂數閲嶆柊鎻掍笂锛岀瓑 10 绉掑啀鎼?
Q: 閰嶇綉椤甸潰鎵撲笉寮€
A: 鎵嬪姩鍦ㄦ祻瑙堝櫒杈撳叆 `192.168.4.1`

Q: WiFi 杩炴帴澶辫触
A: 纭鏄?2.4GHz 缃戠粶 (ESP8266 涓嶆敮鎸?5GHz)

Q: LED 鐏笉浜?A: 妫€鏌ユ帴绾匡紝DATA 绾挎帴 D4 (GPIO2)

Q: 鐏笉鍙樿壊
A: 妫€鏌ョ數鑴戞槸鍚﹁兘涓婄綉锛屼簯绔湇鍔″櫒鏄惁姝ｅ父

## 鎶€鏈爤

- ESP8266 (NodeMCU v3 / D1 Mini)
- Arduino CLI
- Adafruit NeoPixel
- Adafruit SSD1306
- Flask (Python)
- Serv00 浜戞湇鍔″櫒

## 璁稿彲璇?
MIT License

## 浣滆€?
leeredstar


