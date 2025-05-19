#!/usr/bin/env python3
# run.py
# script to setup flask server and launch webpage

import subprocess
import os
import time
import webbrowser
import signal
import sys

# CONFIG
FLASK_PORT = 8000
FRONTEND_PAGE = f"http://localhost:{FLASK_PORT}/frontend/index.html"
SOLVER_DIR = os.path.join("backend", "solver")
SERVER_FILE = os.path.join("backend", "server.py")

def build_c_solver():
    print("[INFO] Building C solver...")
    subprocess.run(["make"], cwd=SOLVER_DIR, check=True)

def start_backend():
    print("[INFO] Starting Flask server...")
    env = os.environ.copy()
    env["FLASK_APP"] = SERVER_FILE
    env["FLASK_ENV"] = "development"
    return subprocess.Popen(["flask", "run", "--port", str(FLASK_PORT)], env=env)

def open_browser():
    print(f"[INFO] Opening {FRONTEND_PAGE}")
    webbrowser.open(FRONTEND_PAGE)

def main():
    try:
        build_c_solver()
        flask_proc = start_backend()

        # Wait a bit for Flask to boot
        time.sleep(2)

        open_browser()

        print("[INFO] Press Ctrl+C to stop everything.")
        flask_proc.wait()

    except KeyboardInterrupt:
        print("\n[INFO] Caught interrupt, shutting down...")
        flask_proc.send_signal(signal.SIGINT)
        flask_proc.wait()
        print("[INFO] Server shut down cleanly.")
        sys.exit(0)

if __name__ == "__main__":
    main()

