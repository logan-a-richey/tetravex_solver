// editor and solver js script

async function solve() {
  const boardSize = document.getElementById("boardSize").value;
  const boardString = document.getElementById("boardString").value;

  const response = await fetch('http://localhost:5000/solve', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      board_size: parseInt(boardSize),
      board_string: boardString
    })
  });

  const result = await response.json();
  document.getElementById("solutionText").textContent = result.solution || result.error;
}

