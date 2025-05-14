// main.cpp

#include "generator.h"
#include "solver.h"
#include "pretty_printer.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage:\n"
                  << "  ./solver_program --random <size>\n"
                  << "  ./solver_program --solve <tile1> <tile2> ...\n";
        return 1;
    }

    std::string mode = argv[1];
    std::vector<std::string> args(argv + 2, argv + argc);

    std::string tile_string;
    int dim;

    if (mode == "--random") {
        if (args.size() != 1 || !std::all_of(args[0].begin(), args[0].end(), ::isdigit)) {
            std::cerr << "Error: --random requires a single integer argument.\n";
            return 1;
        }

        dim = std::stoi(args[0]);
        std::cout << "Generating " << dim << "x" << dim << " puzzle...\n";
        tile_string = Generator::generate(dim);
    }
    else if (mode == "--solve") {
        int tile_count = args.size();
        dim = static_cast<int>(std::sqrt(tile_count));
        if (dim * dim != tile_count) {
            std::cerr << "Error: Tile count must form a square grid.\n";
            return 1;
        }

        std::ostringstream oss;
        for (size_t i = 0; i < args.size(); ++i) {
            oss << args[i];
            if (i != args.size() - 1) oss << " ";
        }
        tile_string = oss.str();
        std::cout << "Solving " << dim << "x" << dim << " puzzle from input...\n";
    }
    else {
        std::cerr << "Unknown mode: " << mode << "\n";
        std::cerr << "Use --random or --solve\n";
        return 1;
    }

    Solver solver(tile_string, dim);
    std::string solution = solver.solve();

    PrettyPrinter printer(dim);
    printer.print_board(solution);

    return 0;
}

