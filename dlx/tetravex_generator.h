// gen.h

#pragma once

#include <string>
#include <vector>

#include "tile.h"

class TetravexGenerator {
public:
    
    std::string gen_str(int board_size, int edge_range);
    
    std::vector<Tile> gen_vec(int board_size, int edge_range);
};

