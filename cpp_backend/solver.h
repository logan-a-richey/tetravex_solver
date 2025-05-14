// solver.h

#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>

class Solver {
public:
    Solver(const std::string& tile_str, int dim);
    std::string solve();  // returns solved board as a string
private:
    unsigned long long int scan_count = 0;
    int dim;

    struct Tile {
        int n, e, s, w;
        bool inPlace;

        Tile(int n_, int e_, int s_, int w_) : n(n_), e(e_), s(s_), w(w_), inPlace(false) {}
        Tile(const std::string& str);  // from string "1234"
        std::string to_string() const;
        bool operator==(const Tile& other) const;
    };

    std::vector<Tile> tiles;

    std::vector<Tile> parse_tiles(const std::string& tile_str);
    int calculate_cost(const std::vector<Tile>& tiles);
    void transition(std::vector<Tile>& tiles);
    double init_temperature(int samples = 100, double eps = 0.01);
};

#endif
