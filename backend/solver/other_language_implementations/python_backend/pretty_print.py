# pretty_print.py

from typing import List

BOARD_TYPE = List[List[str]]

class PrettyPrint:
    @staticmetohd
    def get_simple_ascii(board: BOARD_TYPE) -> str:
        size = len(board[0])
        out = ""
        for i in range(size):
            for j in range(size):
                piece = board[i][j]
                out += piece.get_string()
                out += " "
            out += "\n"
        return out

    @staticmethod
    def get_complex_ascii(board: BOARD_TYPE) -> str:
        size = len(board[0])
        div = "{}+\n".format("+---" * size)
        out = div 
        for i in range(size):
            for r in range(3):
                for j in range(size):
                    piece = board[i][j]
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
