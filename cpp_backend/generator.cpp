// generator.cpp
// code to generate a tetravex puzzle string

// generator.cpp
#include "generator.h"
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Piece {
public:
    int n, e, s, w;

    std::string get_id() const {
        std::ostringstream oss;
        oss << n << e << s << w;
        return oss.str();
    }
};

std::string Generator::generate(int size) {
    using Board = std::vector<std::vector<Piece>>;
    Board board(size, std::vector<Piece>(size));

    // Random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> digit(0, 9);

    // Generate a solved board with matching edges
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Piece& p = board[i][j];

            // Default random values
            p.n = digit(rng);
            p.e = digit(rng);
            p.s = digit(rng);
            p.w = digit(rng);

            if (j >= 1) p.w = board[i][j - 1].e;     // match west edge
            if (i >= 1) p.n = board[i - 1][j].s;     // match north edge
        }
    }

    // Flatten board into a 1D vector for shuffling
    std::vector<Piece> flat;
    for (const auto& row : board)
        flat.insert(flat.end(), row.begin(), row.end());

    std::shuffle(flat.begin(), flat.end(), rng);

    // Build final output string: "1234 5678 9012 ..."
    std::ostringstream result;
    for (size_t k = 0; k < flat.size(); ++k) {
        result << flat[k].get_id();
        if (k + 1 < flat.size()) result << ' ';
    }

    return result.str();
}
