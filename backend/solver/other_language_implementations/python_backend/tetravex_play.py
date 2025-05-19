#!/usr/bin/env python3
# tetravex_play.py

import re
from typing import List

class TetravexPlay:
    def __init__(self, size=3):
        self.size = size
        
        # TODO fix me with real values
        self.grid_left: List[List[str]] = [["0123" for _ in range(size)] for _ in range(size)]
        self.grid_right: List[List[str]] = [["...." for _ in range(size)] for _ in range(size)]
        
        self.playing = False

    def print_board(self):
        print("\nLeft Grid       ->       Right Grid")
        for row in range(self.size):
            left_row = " ".join(self.grid_left[row])
            right_row = " ".join(self.grid_right[row])
            print(f"{left_row}    ->    {right_row}")
        print()

    def is_solved(self, matrix: List[List[str]]) -> bool:
        size = self.size
        target = 2 * size * (size - 1)  # Each internal edge is shared

        count = 0
        for i in range(size):
            for j in range(size):
                sq = matrix[i][j]
                if sq == "....":
                    continue  # Skip empty

                # Up
                if i > 0 and matrix[i - 1][j] != "....":
                    if sq[0] == matrix[i - 1][j][2]:
                        count += 1
                # Right
                if j < size - 1 and matrix[i][j + 1] != "....":
                    if sq[1] == matrix[i][j + 1][3]:
                        count += 1
                # Down
                if i < size - 1 and matrix[i + 1][j] != "....":
                    if sq[2] == matrix[i + 1][j][0]:
                        count += 1
                # Left
                if j > 0 and matrix[i][j - 1] != "....":
                    if sq[3] == matrix[i][j - 1][1]:
                        count += 1

        return count == target

    def play(self):
        self.playing = True
        while self.playing:
            self.print_board()
            print("Valid move format: <src_grid> <src_row> <src_col> <dst_grid> <dst_row> <dst_col>")
            user_input = input("Make move: ")
            numbers = re.findall(r'\d+', user_input)

            if len(numbers) != 6:
                print("Invalid input. Expected 6 numbers.")
                continue

            src_g, src_i, src_j, dst_g, dst_i, dst_j = map(int, numbers)

            if src_g not in [0, 1] or dst_g not in [0, 1]:
                print("Grid index must be 0 (left) or 1 (right).")
                continue

            if not all(0 <= idx < self.size for idx in [src_i, src_j, dst_i, dst_j]):
                print(f"Row/Col must be between 0 and {self.size - 1}.")
                continue

            grids = [self.grid_left, self.grid_right]

            # Swap tiles
            src_tile = grids[src_g][src_i][src_j]
            dst_tile = grids[dst_g][dst_i][dst_j]
            grids[src_g][src_i][src_j], grids[dst_g][dst_i][dst_j] = dst_tile, src_tile

            if self.is_solved(self.grid_right):
                self.print_board()
                print("Puzzle solved! Congratulations!")
                self.playing = False

if __name__ == "__main__":
    game = TetravexPlay(size=2)
    game.play()

