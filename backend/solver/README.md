# Tetravex Solver (C Implementation)

- This is a simulated annealing-based solver for the classic Tetravex puzzle.
- Implemented in ANSI C for performance and control. 

## Overview

- Tetravex is an edge-matching puzzle where tiles must be placed on an `N x N` grid such that all adjacent edges match.
- This solver uses simulated annealing to efficiently search the solution space for valid configurations.

## Build Instructions

To compile the solver, use the provided `Makefile`:

```sh
make
````

Alternatively, compile manually:

```sh
gcc main.c solver.c tile.c -o tetravex_solver -lm
```

Dependencies:

* Standard C library (`stdlib.h`, `stdio.h`, `math.h`, `string.h`)
* No third-party libraries

## Usage

```sh
./tetravex_solver <board_size> <tile1> <tile2> ... <tileN>
```

* `board_size`: Integer representing the width and height of the board.
* Each `tile`: A string of 4 digits representing the north, east, south, and west edges of the tile in that order.

### Example

```sh
./tetravex_solver 2 5961 9179 7814 6898
```

This represents a 2x2 board with the following tiles:

```
Tile 1: N=1 E=2 S=3 W=4
Tile 2: N=2 E=3 S=4 W=1
Tile 3: N=3 E=4 S=1 W=2
Tile 4: N=4 E=1 S=2 W=3
```

## Algorithm Details

* **Simulated Annealing**: Starts from a random permutation of the tile list and applies probabilistic swaps to reduce mismatches.
* **Cost Function**: Counts total mismatches between adjacent tile edges.
* **Cooling Schedule**: Geometric decay with configurable initial temperature, minimum temperature, and decay rate.
* **Termination**: Stops when a valid solution (zero-cost state) is found.

## Output

The program prints a space-separated list of the final tile arrangement when solved.

Example:

```
total positions scanned: 18696
Solution: 9179 5961 7814 6898
```

## File Structure

```
.
├── main.c          // Entry point, handles command-line arguments
├── solver.c/.h     // Simulated annealing core logic
├── tile.c/.h       // Tile representation and string utilities
├── Makefile        // Build instructions
└── README.md       // Project documentation
```

## Limitations

* Assumes valid input (tile strings are 4-digit numbers, no malformed data).
* Valid puzzle (solution exists)
* Runtime grows with board size (due to increased permutation space).
* Single-threaded implementation.

## Future Improvements

* Add timeout or maximum iteration cap
* Support for file-based input/output
* Multithreaded variants for parallel search
* Heuristic initialization strategies
* Visual debugging output (ASCII board or image export)

## License

This project is released under the MIT License.

