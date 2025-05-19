#include "pretty_printer.h"
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

    // Fill board from flat string
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            ss >> token;
            board[i][j] = Tile(token);
        }
    }

    std::string output;
    std::string divider = repeat("+---", dim) + "+\n";

    for (int i = 0; i < dim; ++i) {
        output += repeat("+---", dim) + "+\n";  // Top border

        // Row 1: north
        for (int j = 0; j < dim; ++j) {
            output += "| " + std::string(1, board[i][j].n) + " ";
        }
        output += "|\n";

        // Row 2: west and east
        for (int j = 0; j < dim; ++j) {
            output += "|" + std::string(1, board[i][j].w) + " " + std::string(1, board[i][j].e);
        }
        output += "|\n";

        // Row 3: south
        for (int j = 0; j < dim; ++j) {
            output += "| " + std::string(1, board[i][j].s) + " ";
        }
        output += "|\n";
    }

    output += repeat("+---", dim) + "+\n";  // Final border
    std::cout << output;
}

void PrettyPrinter::print_board(const std::string& flat_string) {
    pretty_print_board(flat_string);
}
