# puzzle_solver.py

import random
import math

from copy import deepcopy

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


class PuzzleSolver:
    def __init__(self, tile_str, dim):
        self.dim = dim
        self.tiles = self.parse_tiles(tile_str)
        assert len(self.tiles) == dim * dim

    def parse_tiles(self, tile_str):
        parts = tile_str.strip().split()
        return [Tile(s) for s in parts]

    def calculate_cost(self, tiles):
        size = self.dim
        cost = 0
        for i in range(size):
            for j in range(size):
                idx = i * size + j
                tile = tiles[idx]
                # north neighbor
                if i > 0 and tile.n != tiles[(i - 1) * size + j].s:
                    cost += 1
                # west neighbor
                if j > 0 and tile.w != tiles[i * size + (j - 1)].e:
                    cost += 1
                # south neighbor
                if i < size - 1 and tile.s != tiles[(i + 1) * size + j].n:
                    cost += 1
                # east neighbor
                if j < size - 1 and tile.e != tiles[i * size + (j + 1)].w:
                    cost += 1
        return cost

    def transition(self, tiles):
        size = self.dim
        total = size * size
        i = random.randint(0, total - 1)
        while tiles[i].inPlace:
            i = random.randint(0, total - 1)
        j = random.randint(0, total - 1)
        while (tiles[j].inPlace or j == i):
            j = random.randint(0, total - 1)
        tiles[i], tiles[j] = tiles[j], tiles[i]

    def init_temperature(self, samples=100, eps=0.01):
        T1 = 0
        T2 = 1_000_000
        T = T2
        tiles = deepcopy(self.tiles)
        size = self.dim

        while (T2 - T1) > 1:
            T = (T1 + T2) / 2
            accepted = 0
            for _ in range(samples):
                a, b = random.sample(range(size * size), 2)
                while tiles[a].inPlace:
                    a = random.randint(0, size * size - 1)
                while tiles[b].inPlace or a == b:
                    b = random.randint(0, size * size - 1)

                before = self.calculate_cost(tiles)
                tiles[a], tiles[b] = tiles[b], tiles[a]
                after = self.calculate_cost(tiles)
                delta = after - before
                if delta <= 0 or math.exp(-delta / T) > 1 - eps:
                    accepted += 1
                tiles[a], tiles[b] = tiles[b], tiles[a]  # undo
            if accepted >= 0.98 * samples:
                T2 = T
            else:
                T1 = T
        return T

    def solve(self):
        tiles = deepcopy(self.tiles)
        size = self.dim
        cost = self.calculate_cost(tiles)
        T = self.init_temperature()
        Tmin = 0.8
        alpha = 0.999

        rng = random.Random()
        while cost > 0:
            proposed = deepcopy(tiles)
            self.transition(proposed)
            new_cost = self.calculate_cost(proposed)
            delta = new_cost - cost

            if delta <= 0:
                tiles = proposed
                cost = new_cost
            else:
                p = math.exp(-delta / T)
                if rng.random() < p:
                    tiles = proposed
                    cost = new_cost

            if T > Tmin:
                T *= alpha
            else:
                T = Tmin

        self.tiles = tiles  # store solution
        return tiles

    def print_board(self):
        for i in range(self.dim):
            row = self.tiles[i * self.dim:(i + 1) * self.dim]
            print(" ".join(str(t) for t in row))

