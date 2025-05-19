#!/usr/bin/env python3
# server.py

from flask import Flask, request, jsonify
import subprocess
import os
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Allow frontend JS to talk to backend

@app.route('/solve', methods=['POST'])
def solve():
    data = request.get_json()
    size = str(data.get('board_size'))
    board = data.get('board_string')

    try:
        result = subprocess.run(
            ['./tetravex_solver', size, board],
            capture_output=True,
            text=True,
            check=True,
            cwd=os.path.dirname(__file__)  # run in backend dir
        )
        return jsonify({'solution': result.stdout})
    except subprocess.CalledProcessError as e:
        return jsonify({'error': e.stderr}), 500

if __name__ == '__main__':
    app.run(debug=True)

