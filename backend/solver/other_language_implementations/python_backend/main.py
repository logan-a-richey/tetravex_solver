#!/usr/bin/env python3
# main.py

import sys
import math
from typing import List, Callable

from tetravex_play import TetravexPlay
from tetravex_solver import TetravexSolver
from tetravex_generator import TetravexGenerator


def is_perfect_square(n: int) -> bool:
    return n >= 0 and int(math.isqrt(n)) ** 2 == n


def show_usage() -> None:
    prog = sys.argv[0]
    print("Usage:")
    print(f"    {prog} --solve <tile tile ...>     # Solve puzzle from tiles")
    print(f"    {prog} --play <size>               # Play Tetravex game")
    print(f"    {prog} --random <size>             # Generate and solve random puzzle")


def handle_solve(args: List[str]) -> int:
    if len(args) == 0:
        print("Error: No tile arguments provided.")
        return 1

    for i, tile in enumerate(args):
        if len(tile) != 4:
            print(f"Invalid tile argument at position {i + 1}: '{tile}' (must be 4 characters)")
            return 1

    if not is_perfect_square(len(args)):
        print("Error: Number of tiles must be a perfect square.")
        return 1

    print("[INFO] mode = solve cmdline")
    puzzle = args

    solver = TetravexSolver()
    result = solver.solve(puzzle)

    print(result)
    return 0


def handle_play(args: List[str]) -> int:
    if len(args) != 1:
        print("Error: --play requires a single integer argument.")
        return 1

    try:
        size = int(args[0])
        if size <= 0:
            raise ValueError("Size must be positive.")
    except ValueError as e:
        print(f"Invalid size argument for --play: {e}")
        return 1

    print("[INFO] mode = play cmdline")
    game = TetravexPlay()
    game.play(size)
    return 0


def handle_random(args: List[str]) -> int:
    if len(args) != 1:
        print("Error: --random requires a single integer argument.")
        return 1

    try:
        size = int(args[0])
        if size <= 0:
            raise ValueError("Size must be positive.")
    except ValueError as e:
        print(f"Invalid size argument for --random: {e}")
        return 1

    print("[INFO] mode = solve random")
    gen = TetravexGenerator()
    puzzle = gen.generate(size)

    solver = TetravexSolver()
    result = solver.solve(puzzle)

    print(result)
    return 0


def main() -> int:
    if len(sys.argv) < 2:
        show_usage()
        return 1

    mode = sys.argv[1]
    args = sys.argv[2:]

    dispatch: dict[str, Callable[[List[str]], int]] = {
        "--solve": handle_solve,
        "--play": handle_play,
        "--random": handle_random,
    }

    handler = dispatch.get(mode)
    if handler is None:
        print(f"Invalid mode: {mode}")
        show_usage()
        return 1

    return handler(args)


if __name__ == "__main__":
    sys.exit(main())

