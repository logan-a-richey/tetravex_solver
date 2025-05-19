// main.c
// program to solve tetravex puzzles from the cmdline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tile.h"
#include "solver.h"

static void display_usage_error() {
    printf("Usage: ./main <board_size> <tile> <tile> <tile> ...\n");
    printf("Each <tile> should be 4 digits representing N,E,S,W edges.\n");
}

int main(int argc, char** argv) {
    // check cmdline input
    if (argc < 3) {
        display_usage_error();
        return 1;
    }

    const int board_size = atoi(argv[1]);
    const int num_tiles = board_size * board_size;

    if (argc != num_tiles + 2) {
        printf("Error: expected %d params.\n", num_tiles + 2);
        display_usage_error();
        return 1;
    }

    // parse board
    Tile* tile_list = malloc(sizeof(Tile) * num_tiles);
    for (int i = 0; i < num_tiles; i++) {
        char* tile_str = argv[i + 2];
        if (strlen(tile_str) != 4) {
            printf("Error: Tile %d '%s' must be 4 characters long.\n", i, tile_str);
            free(tile_list);
            return 1;
        }
        tile_list[i] = parse_tile(tile_str);
    }

    // solve puzzle
    char* solution = solve_tetravex(tile_list, board_size);
    printf("Solution: %s\n", solution);

    // clean up
    free(solution);
    free(tile_list);

    return 0;
}
