---
name: vibe-lamp
description: "Signal the Task LED vibe lamp at meaningful work stages. Use when shell access is available and Codex is performing coding tasks. The lamp changes color to reflect AI work phases: thinking=blue, working=purple, success=green, error=red, idle=dim white. Trigger on every meaningful stage transition during coding work."
---

# Vibe Lamp

Control the physical Task LED lamp during Codex work sessions.

## When to Signal

Send ONE signal per meaningful stage transition:

| Stage | When | Color |
|-------|------|-------|
| thinking | Before planning or reasoning | Blue |
| exploring | Before reading/searching files | Blue |
| coding | Before editing files | Purple |
| running | Before general shell commands | Purple |
| testing | Before test/build/lint | Purple |
| reviewing | While checking outputs | Purple |
| success | Work completes successfully | Green |
| error | Command fails or task blocked | Red |
| waiting | User input needed | Dim white |
| idle | After final response | Dim white |

## How to Signal

```powershell
python D:\zhuanqian\danpianji\codex_lamp_cloud.py <stage> "<message>"
```

Examples:
```powershell
python D:\zhuanqian\danpianji\codex_lamp_cloud.py thinking "Planning"
python D:\zhuanqian\danpianji\codex_lamp_cloud.py coding "Editing code"
python D:\zhuanqian\danpianji\codex_lamp_cloud.py success "Done"
python D:\zhuanqian\danpianji\codex_lamp_cloud.py idle "Standby"
```

## Rules

1. Do NOT fail or delay user work if the lamp script or cloud server is unavailable.
2. One event per stage is enough. Do not spam.
3. Always send `idle` after final response or when no active work remains.
4. The script works via cloud HTTP (s11.serv00.com:13470). No local network to device needed.
5. Script path: `D:\zhuanqian\danpianji\codex_lamp_cloud.py`
