// main.cpp

#include <iostream>
#include <string>
#include <cstdlib>  // for std::atoi

#include "solver.h"
#include "generator.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <board_size>\n";
        return 1;
    }

    int size = std::atoi(argv[1]);
    if (size <= 0) {
        std::cerr << "Invalid size: must be a positive integer.\n";
        return 1;
    }

    Generator generator;
    std::string puzzle = generator.generate(size);

    std::cout << "Generated Tetravex puzzle (" << size << "x" << size << "):\n";
    std::cout << puzzle << "\n";

    Solver solver(puzzle, size);
    std::string solution = solver.solve();
    // std::cout << "Solution:\n" << solution << std::endl;
    std::cout << solution << std::endl;

    return 0;
}
