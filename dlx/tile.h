// tile.h

#pragma once

struct Tile{
    int id;             // unique identifier
    int i, j;           // position in grid[i][j]
    int n, e, s, w;    // tile edge values
};
