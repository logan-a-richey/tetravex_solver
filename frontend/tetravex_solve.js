// tetravex_solve.js

const colorMap = {
  0: '#FFFFFF', 1: '#FF0000', 2: '#FFA500', 3: '#FFFF00',
  4: '#00FF00', 5: '#00FFFF', 6: '#0000FF',
  7: '#FF00FF', 8: '#808080', 9: '#000000'
};

let tileData = [];
let boardSize = 3;

function parseBoardString(str, size) {
  const tokens = str.trim().split(/\s+/);
  if (tokens.length !== size * size) return null;
  return tokens.map(tile => tile.padStart(4, '0000').slice(0, 4));
}

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

    // Draw 4 triangles NESW
    const cx = x + tileSize / 2;
    const cy = y + tileSize / 2;
    const r = tileSize;

    const edges = ['N', 'E', 'S', 'W'];
    const points = {
      N: [[x, y], [x + r, y], [cx, cy]],
      E: [[x + r, y], [x + r, y + r], [cx, cy]],
      S: [[x, y + r], [x + r, y + r], [cx, cy]],
      W: [[x, y], [x, y + r], [cx, cy]],
    };

    edges.forEach((dir, i) => {
      const val = parseInt(tile[i]);
      ctx.fillStyle = colorMap[val] || '#CCCCCC';
      ctx.beginPath();
      const tri = points[dir];
      ctx.moveTo(tri[0][0], tri[0][1]);
      ctx.lineTo(tri[1][0], tri[1][1]);
      ctx.lineTo(tri[2][0], tri[2][1]);
      ctx.closePath();
      ctx.fill();

      // Draw text
      ctx.fillStyle = '#000000';
      ctx.font = `${tileSize / 6}px sans-serif`;
      const tx = (tri[0][0] + tri[1][0] + tri[2][0]) / 3;
      const ty = (tri[0][1] + tri[1][1] + tri[2][1]) / 3 + 4;
      ctx.fillText(tile[i], tx - 4, ty);
    });

    ctx.strokeStyle = '#000000';
    ctx.strokeRect(x, y, tileSize, tileSize);
  });
}

document.getElementById("boardString").addEventListener("input", () => {
  boardSize = parseInt(document.getElementById("boardSize").value);
  const tiles = parseBoardString(document.getElementById("boardString").value, boardSize);
  if (tiles) {
    tileData = tiles;
    drawBoard("inputBoard", tileData, boardSize);
  }
});

async function solve() {
  const boardString = document.getElementById("boardString").value;
  const size = parseInt(document.getElementById("boardSize").value);
  const res = await fetch("http://localhost:5000/solve", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ board_size: size, board_string: boardString })
  });

  const data = await res.json();
  if (data.solution) {
    const lines = data.solution.trim().split('\n');
    const solutionTiles = lines.map(line => line.trim()).filter(line => /^[0-9]{4}$/.test(line));
    drawBoard("solutionBoard", solutionTiles, size);

    const metaLine = lines.find(line => line.includes("solved in")) || "";
    document.getElementById("solutionStats").textContent = metaLine;
  } else {
    document.getElementById("solutionStats").textContent = data.error || "Failed to solve.";
  }
}

