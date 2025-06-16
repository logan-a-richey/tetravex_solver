// main.cpp
// entry point for program

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <limits>

#include "tile.h"
#include "tetravex_generator.h"
#include "tetravex_dlx_solver.h"

// Forward declarations
void generate_puzzle();
void solve_puzzle();
void clear_input_stream();

int main(void) {
    std::string user_input;

    while (true) {
        std::cout << "\n--- Tetravex Solver ---\n"
                  << "What would you like to do?\n"
                  << "[1] Generate new puzzle\n"
                  << "[2] Solve existing puzzle\n"
                  << "[q] Quit\n"
                  << "Input: ";
        std::getline(std::cin, user_input);

        if (user_input == "1") {
            generate_puzzle();
        } else if (user_input == "2") {
            solve_puzzle();
        } else if (user_input == "q" || user_input == "Q") {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

void generate_puzzle() {
    std::string input;
    int board_size = 0;
    int value_range = 0;

    std::cout << "Enter board size (e.g., 4): ";
    std::getline(std::cin, input);
    try {
        board_size = std::stoi(input);
    } catch (...) {
        std::cout << "Invalid input for board size.\n";
        return;
    }

    std::cout << "Enter number of tile values (e.g., 10): ";
    std::getline(std::cin, input);
    try {
        value_range = std::stoi(input);
    } catch (...) {
        std::cout << "Invalid input for tile value range.\n";
        return;
    }

    std::cout << "Generating puzzle of size " << board_size 
              << " with values 0 to " << value_range - 1 << "...\n";
    // TODO: Call actual puzzle generation logic here
}

void solve_puzzle() {
    std::string puzzle_input;

    std::cout << "Enter puzzle string (e.g., 3 0123 1230 3012 ...):\n";
    std::getline(std::cin, puzzle_input);

    // TODO: Validate and parse puzzle_input
    std::cout << "Solving puzzle: " << puzzle_input << "\n";

    // TODO: Call solving logic
}

