# Task LED - Codex Vibe Lamp

ESP8266 智能氛围灯，根据 Codex AI 编程助手的工作状态自动变换颜色。

## 功能特点

- **WiFi 自动配网** - 手机连接 AP 自动弹出设置页面
- **云端控制** - 通过 Serv00 服务器中转指令
- **4 种颜色** - 蓝色(思考)、紫色(编码)、绿色(成功)、红色(错误)
- **待机白灯** - 空闲时微亮白色，证明灯带正常
- **长按重置** - FLASH 按钮 3 秒恢复出厂设置
- **OLED 显示** - 显示 IP 地址和当前状态

## 硬件需求

- ESP8266 0.96 OLED 集成板
- WS2812B LED 灯带 (30颗)
- USB 数据线

## 接线方式

```
LED灯带 GND  → 板子 GND
LED灯带 VCC  → 板子 5V (或 VU)
LED灯带 DATA → 板子 D4 (GPIO2)
OLED 屏幕    → 已集成 (SDA=D6, SCL=D5)
```

## 快速开始

### 1. 安装 Arduino CLI

```powershell
# 下载 Arduino CLI
# https://arduino.github.io/arduino-cli/latest/installation/

# 安装 ESP8266 平台
arduino-cli core install esp8266:esp8266

# 安装所需库
arduino-cli lib install "Adafruit NeoPixel"
arduino-cli lib install "Adafruit SSD1306"
arduino-cli lib install "ArduinoJson"
```

### 2. 编译固件

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 3. 上传固件

```powershell
# 查看串口
arduino-cli board list

# 上传 (替换 COM3 为你的串口)
arduino-cli upload --fqbn esp8266:esp8266:nodemcuv2 -p COM6 TaskLED_Cloud/TaskLED_Cloud.ino
```

### 4. 配置 WiFi

1. 插上电源，灯带亮白色
2. 手机搜索 WiFi：`Task-LED-Setup`
3. 连接后自动弹出设置页面
4. 输入 WiFi 名称和密码
5. 点击 Connect
6. 等待绿灯闪 5 下 = 配置成功

### 5. 部署云端服务器

```powershell
# 登录 Serv00 服务器
ssh billgatesxing11@s11.serv00.com -p 22

# 上传 server.py
scp -P 22 cloud/server.py billgatesxing11@s11.serv00.com:~/

# 安装依赖
pip install flask

# 运行服务器 (后台)
nohup python server.py > server.log 2>&1 &
```

### 6. 安装 Codex 技能

```powershell
# 复制技能到 Codex 技能目录
Copy-Item -Recurse vibe-lamp-skill/vibe-lamp ~/.codex/skills/
```

## 项目结构

```
.
├── TaskLED_Cloud/
│   └── TaskLED_Cloud.ino    # ESP8266 固件
├── codex_lamp_cloud.py      # PC 控制脚本
├── cloud/
│   └── server.py            # 云端服务器
├── vibe-lamp-skill/
│   └── vibe-lamp/
│       └── SKILL.md         # Codex 技能
├── TEST_GUIDE.md            # 自测文档
└── README.md
```

## 工作原理

```
Codex 工作 → PC 脚本 → 云端服务器 → ESP8266 轮询 → LED 变色
```

1. Codex 执行任务时，自动调用 `codex_lamp_cloud.py`
2. 脚本发送 HTTP POST 到 Serv00 服务器
3. ESP8266 每 2 秒轮询服务器获取颜色
4. 收到颜色后控制 LED 灯带变色

## 颜色定义

| 状态 | 颜色 | RGB |
|------|------|-----|
| thinking | 蓝色 | 0, 0, 255 |
| working | 紫色 | 180, 0, 255 |
| success | 绿色 | 0, 255, 0 |
| error | 红色 | 255, 0, 0 |
| standby | 白色 (微亮) | 20, 20, 20 |

## 恢复出厂设置

**方法 1：硬件重置**
- 长按 FLASH 按钮 3 秒
- 等待红灯闪 5 下
- 自动进入配网模式

**方法 2：网页重置**
- 连接 `Task-LED-Setup` WiFi
- 访问 `http://192.168.4.1/reset`
- 确认重置

## 响应时间

| 环节 | 耗时 |
|------|------|
| PC → 云端 | ~550ms |
| 云端 → ESP8266 | ~4.7s |
| 总计 | ~5.3s |

## 故障排查

**Q: 手机搜不到 Task-LED-Setup WiFi**
A: 拔电重新插上，等 10 秒再搜

Q: 配网页面打不开
A: 手动在浏览器输入 `192.168.4.1`

Q: WiFi 连接失败
A: 确认是 2.4GHz 网络 (ESP8266 不支持 5GHz)

Q: LED 灯不亮
A: 检查接线，DATA 线接 D4 (GPIO2)

Q: 灯不变色
A: 检查电脑是否能上网，云端服务器是否正常

## 技术栈

- ESP8266 (NodeMCU v3 / D1 Mini)
- Arduino CLI
- Adafruit NeoPixel
- Adafruit SSD1306
- Flask (Python)
- Serv00 云服务器

## 许可证

MIT License

## 作者

leeredstar
