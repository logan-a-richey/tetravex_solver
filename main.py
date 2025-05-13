#!/usr/bin/env python3

from puzzle_generator import PuzzleGenerator

def main():
    pg = PuzzleGenerator()
    puzzle = pg.generate(size=3)
    
    
    print(puzzle)
    return

if __name__ == "__main__":
    main()

