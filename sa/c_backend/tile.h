// tile.h

#ifndef TILE_H
#define TILE_H

typedef struct {
    int n, e, s, w;
} Tile;

Tile parse_tile(const char* str);     // "1234" -> Tile{1,2,3,4}
char* tile_to_string(const Tile* t);  // Allocates and returns "1234"

#endif
