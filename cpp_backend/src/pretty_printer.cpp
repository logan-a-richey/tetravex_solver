// pretty_printer.cpp

#include "pretty_printer.h"
#include "tile.h"

#include <iostream>
#include <sstream>

PrettyPrinter::PrettyPrinter(int dim) : dim(dim) {}

std::string PrettyPrinter::repeat(const std::string& s, int times) {
    std::string result;
    for (int i = 0; i < times; ++i) result += s;
    return result;
}

void PrettyPrinter::pretty_print_board(const std::string& flat_string) {
    std::stringstream ss(flat_string);
    std::string token;
    std::vector<std::vector<Tile>> board(dim, std::vector<Tile>(dim));

    // fill board from flat string
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            ss >> token;
            board[i][j] = Tile(token);
        }
    }

    std::string output;
    std::string divider = repeat("+---", dim) + "+\n";

    for (int i = 0; i < dim; ++i) {
        // divider
        output += repeat("+---", dim) + "+\n";

        // row 1: north
        for (int j = 0; j < dim; ++j) {
            output += "| " + std::string(1, board[i][j].n) + " ";
        }
        output += "|\n";

        // row 2: west and east
        for (int j = 0; j < dim; ++j) {
            output += "|" + std::string(1, board[i][j].w) + " " + std::string(1, board[i][j].e);
        }
        output += "|\n";

        // row 3: south
        for (int j = 0; j < dim; ++j) {
            output += "| " + std::string(1, board[i][j].s) + " ";
        }
        output += "|\n";
    }

    // add the final border
    output += repeat("+---", dim) + "+\n";

    // print the board string
    std::cout << output;
}

void PrettyPrinter::print_board(const std::string& flat_string) {
    pretty_print_board(flat_string);
}

