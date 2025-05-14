#!/usr/bin/env python3
# main.py

from generator import Generator
from solver import Solver

def main():
    # create a puzzle
    pg = Generator()
    size = 4
    puzzle = pg.generate(size=size)
    print(puzzle)
    
    # solve the puzzle
    solver = Solver(puzzle, dim=size)
    solver.solve()

    solver.print_board()

if __name__ == "__main__":
    main()

