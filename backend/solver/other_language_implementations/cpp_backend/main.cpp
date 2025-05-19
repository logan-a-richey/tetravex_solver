// main.cpp

#include <iostream>
#include <string>
#include <cstdlib>  // for std::atoi

#include "solver.h"
#include "generator.h"
#include "pretty_printer.h"

int main(int argc, char* argv[]) {
    // init program: check usage 
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <board_size>" << std::endl;
        return 1;
    }

    // init program: get board size from cmdline
    int size = std::atoi(argv[1]);
    if (size <= 0) {
        std::cerr << "Invalid size: must be a positive integer." << std::endl;
        return 1;
    }

    // create puzzle
    Generator generator;
    PrettyPrinter printer(size);
    
    std::string puzzle = generator.generate(size);
    std::cout << "Generated Tetravex puzzle (" << size << "x" << size << "):" << std::endl;
    printer.print_board(puzzle);

    // solve puzzle
    Solver solver(puzzle, size);
    
    std::string solution = solver.solve();
    std::cout << "Solution:" << std::endl;
    printer.print_board(solution);

    return 0;
}

