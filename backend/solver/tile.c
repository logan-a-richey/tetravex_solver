// tile.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tile.h"

Tile parse_tile(const char* str) {
    Tile t;
    t.n = str[0] - '0';
    t.e = str[1] - '0';
    t.s = str[2] - '0';
    t.w = str[3] - '0';
    return t;
}

char* tile_to_string(const Tile* t) {
    char* buf = malloc(5); // "1234" + '\0'
    sprintf(buf, "%d%d%d%d", t->n, t->e, t->s, t->w);
    return buf;
}
