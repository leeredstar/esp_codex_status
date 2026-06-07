"""
Codex Vibe Lamp - Cloud Controller (4 Colors)

Simple color mapping:
  thinking = Blue
  working  = Purple
  success  = Green
  error    = Red

Usage:
  python codex_lamp_cloud.py thinking "Planning"
  python codex_lamp_cloud.py working "Editing"
  python codex_lamp_cloud.py success "Done"
  python codex_lamp_cloud.py error "Failed"
"""
import sys
import json
import requests

SERVER_URL = "http://s11.serv00.com:13470"

# No proxy for cloud server
NO_PROXY = {"http": None, "https": None}

# 4 simple colors
PHASE_COLORS = {
    "thinking": (0, 0, 255, "thinking"),
    "working":  (180, 0, 255, "working"),
    "success":  (0, 255, 0, "success"),
    "error":    (255, 0, 0, "error"),
}

# Aliases
ALIASES = {
    "coding": "working", "running": "working", "testing": "working",
    "reviewing": "working", "exploring": "thinking", "planning": "thinking",
    "done": "success", "complete": "success",
    "fail": "error", "failed": "error",
    "idle": "idle", "waiting": "waiting",
}

# Special: idle and waiting turn LEDs off
IDLE_STATES = {"idle", "waiting"}

def send_status(status):
    url = f"{SERVER_URL}/update_status"
    try:
        resp = requests.post(url, json={"status": status}, timeout=10, proxies=NO_PROXY)
        return resp.json()
    except Exception as e:
        return {"ok": False, "error": str(e)}

def send_idle():
    url = f"{SERVER_URL}/set_idle"
    try:
        resp = requests.post(url, timeout=10, proxies=NO_PROXY)
        return resp.json()
    except Exception as e:
        return {"ok": False, "error": str(e)}

def main():
    if len(sys.argv) < 2:
        print("Usage: python codex_lamp_cloud.py <phase> [message]")
        print("Phases: thinking, working, success, error, idle")
        sys.exit(1)

    phase = sys.argv[1].lower()
    message = " ".join(sys.argv[2:]) if len(sys.argv) > 2 else ""

    # Resolve aliases
    phase = ALIASES.get(phase, phase)

    # Idle/waiting -> turn off LEDs
    if phase in IDLE_STATES:
        result = send_idle()
        result["message"] = message or phase
        print(json.dumps(result, indent=2))
        return

    if phase not in PHASE_COLORS:
        print(f"Unknown: {phase}. Use: thinking, working, success, error, idle")
        sys.exit(1)

    r, g, b, label = PHASE_COLORS[phase]
    if not message:
        message = label

    result = send_status(phase)
    result["message"] = message
    print(json.dumps(result, indent=2))

if __name__ == "__main__":
    main()
