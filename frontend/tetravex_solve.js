// tetravex_solve.js

const colorMap = {
  0: '#FFFFFF', 1: '#FF0000', 2: '#FFA500', 3: '#FFFF00',
  4: '#00FF00', 5: '#00FFFF', 6: '#0000FF',
  7: '#FF00FF', 8: '#808080', 9: '#000000'
};

let boardSize = 2;

// Normalize each tile to exactly 4 digits (pad with '0')
function normalizeTile(tileStr) {
  const digits = tileStr.trim().replace(/[^0-9]/g, '');
  return digits.padEnd(4, '0').slice(0, 4);
}

// Build a grid of tiles based on input
function parseBoardInput(size, boardStr) {
  const rawTiles = boardStr.trim().split(/\s+/);
  let tiles = rawTiles.map(normalizeTile);

  const totalTiles = size * size;
  if (tiles.length < totalTiles) {
    while (tiles.length < totalTiles) tiles.push('0000');
  } else if (tiles.length > totalTiles) {
    tiles = tiles.slice(0, totalTiles);
  }

  return tiles;
}

// Draw one board (input or solution)
function drawBoard(canvasId, tiles, size) {
  const canvas = document.getElementById(canvasId);
  const ctx = canvas.getContext('2d');
  const tileSize = canvas.width / size;
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  tiles.forEach((tile, idx) => {
    const row = Math.floor(idx / size);
    const col = idx % size;
    const x = col * tileSize;
    const y = row * tileSize;

    const cx = x + tileSize / 2;
    const cy = y + tileSize / 2;
    const r = tileSize;

    const dirs = ['N', 'E', 'S', 'W'];
    const tris = {
      N: [[x, y], [x + r, y], [cx, cy]],
      E: [[x + r, y], [x + r, y + r], [cx, cy]],
      S: [[x, y + r], [x + r, y + r], [cx, cy]],
      W: [[x, y], [x, y + r], [cx, cy]]
    };

    dirs.forEach((dir, i) => {
      const val = parseInt(tile[i]);
      ctx.fillStyle = colorMap[val] || '#CCCCCC';
      const t = tris[dir];
      ctx.beginPath();
      ctx.moveTo(...t[0]);
      ctx.lineTo(...t[1]);
      ctx.lineTo(...t[2]);
      ctx.closePath();
      ctx.fill();

      ctx.fillStyle = '#000';
      ctx.font = `${tileSize / 5}px sans-serif`;
      const tx = (t[0][0] + t[1][0] + t[2][0]) / 3;
      const ty = (t[0][1] + t[1][1] + t[2][1]) / 3 + 4;
      ctx.fillText(tile[i], tx - 5, ty);
    });

    ctx.strokeStyle = '#000';
    ctx.strokeRect(x, y, tileSize, tileSize);
  });
}

// Hook up live input
function updateInputBoard() {
  boardSize = parseInt(document.getElementById("boardSize").value) || 2;
  const boardStr = document.getElementById("boardString").value;
  const tiles = parseBoardInput(boardSize, boardStr);
  drawBoard("inputBoard", tiles, boardSize);
}

document.getElementById("boardString").addEventListener("input", updateInputBoard);
document.getElementById("boardSize").addEventListener("input", updateInputBoard);

// Solve button
async function solve() {
  const size = parseInt(document.getElementById("boardSize").value);
  const boardStr = document.getElementById("boardString").value;

  const res = await fetch("http://localhost:5000/solve", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ board_size: size, board_string: boardStr })
  });

  const data = await res.json();
  if (data.solution) {
    const lines = data.solution.trim().split('\n');
    const tiles = lines.filter(line => /^[0-9]{4}$/.test(line));
    drawBoard("solutionBoard", tiles, size);

    const meta = lines.find(line => line.includes('solved in')) || '';
    document.getElementById("solutionStats").textContent = meta;
  } else {
    document.getElementById("solutionStats").textContent = data.error || "Solve failed.";
  }
}

// Initial render
window.onload = updateInputBoard;

