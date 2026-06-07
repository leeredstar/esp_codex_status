---
name: vibe-lamp
description: "MANDATORY: Signal the Task LED lamp at EVERY work stage transition. This is REQUIRED, not optional. The lamp MUST change color when Codex works. If you skip sending signals, the user will not see any lamp activity and the product is useless. ALWAYS send lamp signals before and after each work phase."
---

# Vibe Lamp - MANDATORY

**THIS IS NOT OPTIONAL. You MUST send lamp signals at every stage.**

## Required Signals

Send these signals at the EXACT moments specified:

1. **BEFORE any thinking/planning** -> `thinking` (blue)
2. **BEFORE any file reading/searching** -> `exploring` (blue)
3. **BEFORE any code editing** -> `coding` (purple)
4. **BEFORE any shell commands** -> `running` (purple)
5. **BEFORE any tests** -> `testing` (purple)
6. **WHILE checking results** -> `reviewing` (purple)
7. **WHEN work completes** -> `success` (green)
8. **WHEN errors occur** -> `error` (red)
9. **WHEN waiting for user** -> `idle` (white)
10. **AFTER final response** -> `idle` (white)

## How to Signal

```powershell
python D:\zhuanqian\danpianji\codex_lamp_cloud.py <stage> "<message>"
```

## Critical Rules

1. **NEVER skip a signal** - The lamp MUST change at every stage
2. **Send signal BEFORE starting work** - Not after
3. **Send idle AFTER completing work** - Always
4. **One signal per stage** - Don't spam
5. **If script fails, continue working** - Don't block user

## Examples of CORRECT behavior:

```
User: "Help me write a function"
[SEND] python codex_lamp_cloud.py thinking "Planning"
... think about solution ...
[SEND] python codex_lamp_cloud.py coding "Writing function"
... write code ...
[SEND] python codex_lamp_cloud.py success "Function created"
[SEND] python codex_lamp_cloud.py idle "Done"
```

## Examples of WRONG behavior:

```
User: "Help me write a function"
... think about solution ... (NO SIGNAL - WRONG!)
... write code ... (NO SIGNAL - WRONG!)
... done ... (NO SIGNAL - WRONG!)
```

**If you don't send signals, the lamp won't work and the product is useless.**
