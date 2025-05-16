# tile.py

class Tile:
    def __init__(self, tile_str):
        self.n = int(tile_str[0])
        self.e = int(tile_str[1])
        self.s = int(tile_str[2])
        self.w = int(tile_str[3])
        self.inPlace = False

    def __repr__(self):
        return "{}{}{}{}".format(self.n, self.e, self.s, self.w)

    def __eq__(self, other):
        return (self.n, self.e, self.s, self.w) == (other.n, other.e, other.s, other.w)

    def __hash__(self):
        return hash((self.n, self.e, self.s, self.w))
