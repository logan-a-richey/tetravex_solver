# Tetravex
## 🧩 About

**Tetravex** is a classic tile-based puzzle game. The goal is simple: arrange tiles in a grid so that the numbers on adjacent sides match.

This project brings Tetravex to the browser with a playable UI, puzzle editor, and a backend solver. It's a full-stack demonstration of problem-solving, optimization algorithms, and interactive design.

---

## 📦 Project Overview

This project consists of three main components:

* **Playable Web Version** – Solve puzzles directly in your browser.
* **Level Editor** – Create and edit your own puzzles.
* **Solver Algorithm** – Automatically solve puzzles using Simulated Annealing.

## Setup
1. Navigate to the `backend/` directory:
   ```bash
   cd backend/
   ```
2. Install the Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Compile the C solver:
   ```bash
   make
   ```
4. Run the application:
   ```bash
   python3 server.py
   ```
5. Open your web browser and go to:
   ```
   http://localhost:8000
   ```
   (or whatever host/port your server uses)

---

## 🖥️ Tech Stack

### Frontend

* HTML, CSS, JavaScript
* Interactive GUI with multiple views:

  * Home/Hub page
  * Puzzle gameplay
  * Puzzle editing and solver visualization

### Backend

* **Python** with **Flask** for the web server
* **C** for the high-performance solver (Simulated Annealing)

---

## 🔍 Solver Performance & Lessons Learned

I implemented the solver in Python, C++, and C to compare trade-offs between speed and development time:

| Language | Time to Solve 5x5 Puzzle | Notes                                   |
| -------- | ------------------------ | --------------------------------------- |
| Python   | \~30 minutes             | Easy to write, but slow                 |
| C++      | \~10 seconds             | Faster, but verbose and harder to tweak |
| C        | < 0.1 seconds            | Fastest to write and run                |

### Key Takeaways

* **Simulated Annealing**: Learned how to balance temperature schedules, cost functions, and convergence rates.
* **Performance tuning**: C outperformed both Python and C++ in both execution speed and implementation time for this task.
* **Language trade-offs**: Abstractions in C++ provided flexibility, but added complexity and overhead for this specific use case.

---

## 🚧 Next Steps

* [ ] Refine the frontend UI (CSS polish, animations, quality-of-life features)
* [ ] Explore alternative solver strategies (e.g., backtracking, SAT solving)
* [ ] Restructure codebase for modularity and scalability
* [ ] Implement additional browser-playable games with solvers:

  * **Klotski** (sliding block puzzle)
  * **Reversi**
  * **Chess**

---

## Project Significance:

This project is a hands-on demonstration of combining:

* Game logic
* Optimization algorithms
* Performance profiling
* Full-stack deployment

It’s also a step toward building a portfolio of interactive, browser-based games with automated solving capabilities.

