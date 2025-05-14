#!/usr/bin/env python3

from puzzle_generator import PuzzleGenerator
from puzzle_solver import PuzzleSolver

def main():
    # create a puzzle
    pg = PuzzleGenerator()
    size = 6
    puzzle = pg.generate(size=size)
    print(puzzle)
    
    # solve the puzzle
    solver = PuzzleSolver(puzzle, dim=size)
    solver.solve()

    solver.print_board()

if __name__ == "__main__":
    main()

