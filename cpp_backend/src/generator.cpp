// generator.cpp
// code to generate a tetravex puzzle string

#include "generator.h"
#include "tile.h"

#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

// generate a random puzzle
std::string Generator::generate(int size) {
    using Board = std::vector<std::vector<Tile>>;
    Board board(size, std::vector<Tile>(size));

    // random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> digit(0, 9);

    // generate a solved board with matching edges
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Tile& p = board[i][j];

            // default random values
            p.n = digit(rng);
            p.e = digit(rng);
            p.s = digit(rng);
            p.w = digit(rng);

            // match west edge
            if (j >= 1) {
                p.w = board[i][j - 1].e;                 
            }
            // match north edge
            if (i >= 1) {
                p.n = board[i - 1][j].s;     
            }
        }
    }

    // flatten board and shuffle
    std::vector<Tile> flat;
    for (const auto& row : board)
        flat.insert(flat.end(), row.begin(), row.end());

    std::shuffle(flat.begin(), flat.end(), rng);

    // build output string: "1234 5678 9012 ..."
    std::ostringstream result;
    for (size_t k = 0; k < flat.size(); ++k) {
        result << flat[k].get_id();
        if (k + 1 < flat.size()) result << ' ';
    }

    return result.str();
}

