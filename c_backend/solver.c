// solver.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "tile.h"
#include "solver.h"

// keep track of number of positions scanned
int positions_scanned = 0;

// cost: number of mismatches
int calculate_cost(Tile* t, int dim) {
    int cost = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int idx = i * dim + j;
            Tile* tile = &t[idx];

            if (i > 0 && tile->n != t[(i - 1) * dim + j].s){
                cost++;
                positions_scanned++;
            }
            if (j > 0 && tile->w != t[i * dim + (j - 1)].e) {
                cost++;
                positions_scanned++;
            }
            if (i < dim - 1 && tile->s != t[(i + 1) * dim + j].n) {
                cost++;
                positions_scanned++;
            }
            if (j < dim - 1 && tile->e != t[i * dim + (j + 1)].w) {
                cost++;
                positions_scanned++;
            }
        }
    }
    return cost;
}

void transition(Tile* t, int dim) {
    int total = dim * dim;
    int i = rand() % total;
    int j = rand() % total;
    while (j == i) j = rand() % total;
    Tile tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}

double init_temperature(Tile* tiles, int dim, int samples, double eps) {
    double T1 = 0.0, T2 = 1e6, T;
    Tile* copy = malloc(sizeof(Tile) * dim * dim);
    memcpy(copy, tiles, sizeof(Tile) * dim * dim);

    while ((T2 - T1) > 1.0) {
        T = (T1 + T2) / 2.0;
        int accepted = 0;

        for (int k = 0; k < samples; ++k) {
            int a = rand() % (dim * dim);
            int b = rand() % (dim * dim);
            while (b == a) b = rand() % (dim * dim);

            int before = calculate_cost(copy, dim);
            Tile tmp = copy[a];
            copy[a] = copy[b];
            copy[b] = tmp;

            int after = calculate_cost(copy, dim);
            int delta = after - before;

            if (delta <= 0 || exp(-delta / T) > 1.0 - eps) {
                accepted++;
            }

            tmp = copy[a]; copy[a] = copy[b]; copy[b] = tmp;
        }

        if (accepted >= 0.98 * samples) {
            T2 = T;
        } else {
            T1 = T;
        }
    }

    free(copy);
    return T;
}

// main solve method to call
char* solve_tetravex(Tile* tiles, int dim) {
    // reset
    positions_scanned = 0;

    srand(time(NULL));
    int total = dim * dim;

    Tile* current = malloc(sizeof(Tile) * total);
    memcpy(current, tiles, sizeof(Tile) * total);

    int cost = calculate_cost(current, dim);
    double T = init_temperature(current, dim, 100, 0.01);
    double Tmin = 0.8;
    double alpha = 0.999;

    while (cost > 0) {
        Tile* proposed = malloc(sizeof(Tile) * total);
        memcpy(proposed, current, sizeof(Tile) * total);

        transition(proposed, dim);
        int new_cost = calculate_cost(proposed, dim);
        int delta = new_cost - cost;

        if (delta <= 0 || ((double) rand() / RAND_MAX) < exp(-delta / T)) {
            memcpy(current, proposed, sizeof(Tile) * total);
            cost = new_cost;
        }

        T = fmax(T * alpha, Tmin);
        free(proposed);
    }

    // Build result string
    char* result = malloc(5 * total);  // "1234 " * total + '\0'
    result[0] = '\0';

    for (int i = 0; i < total; ++i) {
        char* tile_str = tile_to_string(&current[i]);
        strcat(result, tile_str);
        if (i != total - 1) strcat(result, " ");
        free(tile_str);
    }
    
    printf("total positions scanned: %d\n", positions_scanned);

    free(current);
    return result;
}

