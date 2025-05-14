# Tetravex Solver

A C++ implementation of a solver for the **Tetravex** puzzle game. The puzzle consists of tiles with four edges, and the goal is to arrange the tiles in a grid such that adjacent edges of the tiles match.

This project includes:

* **Generator**: A component that generates random Tetravex puzzles.
* **Solver**: A simulated annealing-based solver for solving generated puzzles.
* **PrettyPrinter**: A utility to print the puzzle in a human-readable, formatted grid.
* **Main Program**: The entry point to generate puzzles and solve them.

---

## Features

* **Puzzle Generation**: Generates random Tetravex puzzles of a given size (e.g., 4x4, 5x5, 6x6).
* **Simulated Annealing Solver**: Uses simulated annealing to solve the puzzle by swapping tiles and minimizing a cost function.
* **Pretty Print**: The solution can be pretty-printed to the console in a well-formatted grid.

## Prerequisites

* A C++11 or later compatible compiler (e.g., GCC, Clang).
* CMake for building the project.

---

## Build Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/tetravex-solver.git
cd tetravex-solver
```

### 2. Compile the Program

You can build the program using `make`. The following command compiles and links all the source files:

```bash
make
```

This will generate the executable `solver_program`.

---

## Usage

### Command Line Arguments

You can specify the size of the puzzle to generate and solve by passing it as a command-line argument.

```bash
./solver_program <size>
```

* `<size>`: The dimension of the puzzle (e.g., `4` for a 4x4 puzzle).

Example usage:

```bash
./solver_program 4
```

This command will generate and solve a 4x4 Tetravex puzzle.

### Pretty Print

Once the solver finds the solution, it will print the solved puzzle in a human-readable format, with edges displayed as follows:

---

---

## Explanation of Files

### `generator.cpp`

Contains the logic for generating random Tetravex puzzles.

### `solver.cpp`

Implements the simulated annealing-based solver. The solver iteratively swaps tiles to minimize the cost function until a solution is found.

### `pretty_printer.cpp`

Contains the `PrettyPrinter` class, which formats the grid and prints it in a nice, readable format.

### `main.cpp`

The main entry point of the program. It handles user input, generates the puzzle, invokes the solver, and prints the solution.

### `solver.h`, `pretty_printer.h`, and `generator.h`

Header files for the respective source files. They define the structures and classes used across the project.

---

## Example Output

For a 4x4 puzzle, the output might look like:

```
Generating a 4x4 puzzle...
Solving the puzzle...

Solution Found! Scanned: 1,234,567 states.

+---+---+---+---+
| 1 | 2 | 3 | 4 |
| 5 | 6 | 7 | 8 |
| 9 | 10 | 11 | 12 |
| 13 | 14 | 15 | 16 |
+---+---+---+---+
```

---

## Performance Notes

* The solver uses **simulated annealing**, which is an optimization technique inspired by thermodynamics. It randomly swaps tiles and accepts swaps based on a temperature parameter.
* Parallelization with **OpenMP** is used to speed up the search process. This significantly reduces the computation time, especially for larger puzzles.
* For a 6x6 puzzle, the solver can take around **300 million** evaluations to solve, and the parallelization reduces this to around **100 million** evaluations.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
