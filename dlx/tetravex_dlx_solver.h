// dlx_solver.h

#pragma once

#include <string>
#include <vector>

#include "tile.h"

class DLX_Solver{
public:
    // Input: a Vector of Tile structs
    // Return: a string solution to the puzzle
    std::string solve(std::vector<Tile>& board);
};


