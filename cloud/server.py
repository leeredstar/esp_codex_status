"""
Codex Vibe Lamp - Cloud Server (Simplified 4 Colors)

Colors:
  thinking  = Blue   (0, 0, 255)
  working   = Purple (180, 0, 255)
  success   = Green  (0, 255, 0)
  error     = Red    (255, 0, 0)

Endpoints:
  POST /update_status  {"status": "thinking"}
  GET  /get_status     -> {"r":0, "g":0, "b":255, "status":"thinking"}
  GET  /health         -> {"ok": true}
"""
from flask import Flask, request, jsonify
from datetime import datetime
import threading

app = Flask(__name__)

# 4 Simple Colors
PHASE_COLORS = {
    "thinking": (0, 0, 255),      # Blue
    "working":  (180, 0, 255),    # Purple
    "success":  (0, 255, 0),      # Green
    "error":    (255, 0, 0),      # Red
}

# Map aliases to main colors
ALIASES = {
    "coding":    "working",
    "running":   "working",
    "testing":   "working",
    "reviewing": "working",
    "exploring": "thinking",
    "planning":  "thinking",
    "done":      "success",
    "complete":  "success",
    "fail":      "error",
    "failed":    "error",
}

state_lock = threading.Lock()
current_state = {
    "r": 0, "g": 0, "b": 0,
    "status": "off",
    "updated_at": None,
}

@app.route("/")
def index():
    return jsonify({"service": "Codex Vibe Lamp", "colors": list(PHASE_COLORS.keys())})

@app.route("/health")
def health():
    return jsonify({"ok": True})

@app.route("/update_status", methods=["POST"])
def update_status():
    data = request.get_json(silent=True)
    if not data:
        return jsonify({"ok": False, "error": "Invalid JSON"}), 400

    with state_lock:
        if "status" in data:
            status = data["status"].strip().lower()
            # Check aliases
            status = ALIASES.get(status, status)
            color = PHASE_COLORS.get(status)
            if color is None:
                return jsonify({"ok": False, "error": f"Unknown: {status}"}), 400
            current_state["r"], current_state["g"], current_state["b"] = color
            current_state["status"] = status
        elif "r" in data and "g" in data and "b" in data:
            current_state["r"] = max(0, min(255, int(data["r"])))
            current_state["g"] = max(0, min(255, int(data["g"])))
            current_state["b"] = max(0, min(255, int(data["b"])))
            current_state["status"] = "custom"
        else:
            return jsonify({"ok": False, "error": "Need status or r,g,b"}), 400

        current_state["updated_at"] = datetime.utcnow().isoformat()

    return jsonify({"ok": True, **current_state})

@app.route("/get_status", methods=["GET"])
def get_status():
    with state_lock:
        return jsonify({
            "r": current_state["r"],
            "g": current_state["g"],
            "b": current_state["b"],
            "status": current_state["status"],
        })


@app.route("/set_idle", methods=["POST"])
def set_idle():
    """Turn LEDs off (idle state)."""
    with state_lock:
        current_state["r"] = 0
        current_state["g"] = 0
        current_state["b"] = 0
        current_state["status"] = "idle"
        current_state["updated_at"] = datetime.utcnow().isoformat()
    return jsonify({"ok": True, "status": "idle"})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=13470, debug=False)
