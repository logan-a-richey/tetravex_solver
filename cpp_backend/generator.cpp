// generator.cpp
// code to generate a tetravex puzzle string

#include <iostream>
#include "generator.h"
#include <string>
#include <cstdlib>
#include <ctime>

class Piece {
public:
    int n, e, s, w;

    std::string get_id() {
        char buffer[5];
        sprintf(buffer, "%d%d%d%d", n, e, s, w);
        return std::string(buffer);
    }
};

std::string Generator::generate(int size) {
    srand(static_cast<unsigned int>(time(0)));

    Piece board[size][size];
    std::string result;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Random values
            board[i][j].n = rand() % 10;
            board[i][j].e = rand() % 10;
            board[i][j].s = rand() % 10;
            board[i][j].w = rand() % 10;

            // Horizontal match (left neighbor)
            if (j >= 1) {
                board[i][j].w = board[i][j - 1].e;
            }

            // Vertical match (top neighbor)
            if (i >= 1) {
                board[i][j].n = board[i - 1][j].s;
            }
        }
    }

    // Build result string
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::string id = board[i][j].get_id();
            result += id + " ";
        }
        result += "\n";
    }

    return result;
}
