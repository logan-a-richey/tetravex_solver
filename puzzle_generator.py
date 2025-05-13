# Tetravex Puzzle Generator

import random
import time

random.seed(time.time())

class Piece:
    def __init__(self):
        self.n = 0
        self.e = 0
        self.s = 0
        self.w = 0

    def get_string(self):
        return "{}{}{}{}".format(self.n, self.e, self.s, self.w)

class PuzzleGenerator:
    def __init__(self):
        self.board = []

    def get_simple_ascii(self) -> str:
        size = len(self.board[0])
        out = ""
        for i in range(size):
            for j in range(size):
                piece = self.board[i][j]
                out += piece.get_string()
                out += " "
            out += "\n"
        return out

    def get_complex_ascii(self):
        size = len(self.board[0])
        div = "{}+\n".format("+---" * size)
        out = div 
        for i in range(size):
            for r in range(3):
                for j in range(size):
                    piece = self.board[i][j]
                    if r == 0:
                        out += "| {} ".format(piece.n)
                    elif r == 1:
                        out += "|{} {}".format(piece.w, piece.e)
                    elif r == 2:
                        out += "| {} ".format(piece.s)
                    else: 
                        pass
                    if j == size - 1:
                        out += "|\n"
            out += "{}".format(div)
        return out
    
    def shuffle_matrix(self, matrix):
        flat = [item for row in matrix for item in row]
        random.shuffle(flat)
        rows, cols = len(matrix), len(matrix[0])
        shuffled = [flat[i * cols:(i + 1) * cols] for i in range(rows)]
        return shuffled

    def generate(self, size=4):
        self.board = [[Piece() for j in range(size)] for i in range(size)]
       
        # generate solution
        for i in range(size):
            for j in range(size):
                piece = self.board[i][j]
                piece.n, piece.e, piece.w, piece.s = [random.randint(1,9) for _ in range(4)]
                
                if i >= 1:
                    adj_piece = self.board[i-1][j]
                    piece.n = adj_piece.s

                if j >= 1:
                    adj_piece = self.board[i][j-1]
                    piece.w = adj_piece.e

                piece = self.board[i][j]
      
        # randomize
        self.board = self.shuffle_matrix(self.board)

        # print
        res = self.get_simple_ascii()
        return res

