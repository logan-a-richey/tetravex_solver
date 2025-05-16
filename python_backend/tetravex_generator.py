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

class Generator:
    def __init__(self):
        self.board = []

    
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

