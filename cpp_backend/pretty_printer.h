#ifndef PRETTYPRINTER_H
#define PRETTYPRINTER_H

#include <string>
#include <vector>

class PrettyPrinter {
public:
    PrettyPrinter(int dim);
    void print_board(const std::string& flat_string);

private:
    int dim;
    struct Tile {
        char n, e, s, w;
        Tile() : n(' '), e(' '), s(' '), w(' ') {} // Default constructor
        Tile(const std::string& str) : n(str[0]), e(str[1]), s(str[2]), w(str[3]) {}
    };
    std::string repeat(const std::string& s, int times);
    void pretty_print_board(const std::string& flat_string);
};

#endif // PRETTYPRINTER_H
