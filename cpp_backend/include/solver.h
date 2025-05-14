// solver.h

#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>

#include "tile.h" // import <class Tile>

class Solver {
public:
    Solver(const std::string& tile_str, int dim);
    std::string solve();  // returns solved board as a string
private:
    unsigned long long int scan_count = 0;
    int dim;

    // TODO fixme
    std::vector<Tile> tiles;

    std::vector<Tile> parse_tiles(const std::string& tile_str);
    int calculate_cost(const std::vector<Tile>& tiles);
    void transition(std::vector<Tile>& tiles);
    double init_temperature(int samples = 100, double eps = 0.01);
};

#endif

