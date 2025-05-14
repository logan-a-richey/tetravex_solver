// main.cpp

#include <iostream>
#include <string>

#include "solver.h"
#include "generator.h"

int main(){
    Generator generator;
    Solver solver;

    int size = 3;
    std::string puzzle = generator.generate(size);

    std::cout << puzzle << std::endl;

    return 0;
}
