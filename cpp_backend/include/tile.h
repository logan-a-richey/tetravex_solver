// tile.h
#ifndef TILE_H
#define TILE_H

#include <string>
#include <stdexcept>
#include <cctype>

class Tile {
public:
    int n = 0, e = 0, s = 0, w = 0;

    // Optional string-based constructor for parsing "1234"
    Tile(const std::string& str) {
        if (str.size() != 4 || !std::all_of(str.begin(), str.end(), ::isdigit)) {
            throw std::invalid_argument("Tile string must be 4 digits (e.g., \"1234\")");
        }

        n = str[0] - '0';
        e = str[1] - '0';
        s = str[2] - '0';
        w = str[3] - '0';
    }

    Tile() = default; // Zero-initialized by default

    std::string to_string() const {
        return std::to_string(n) + std::to_string(e) +
               std::to_string(s) + std::to_string(w);
    }

    bool operator==(const Tile& other) const {
        return n == other.n && e == other.e &&
               s == other.s && w == other.w;
    }
};

#endif

