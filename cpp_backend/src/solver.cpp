// solver.cpp

#include "solver.h"
#include "tile.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <random>

// Format large numbers with commas for readability
std::string format_number_with_commas(unsigned long long int n) {
    if (n == 0) return "0";
    std::string result;
    int count = 0;

    while (n > 0) {
        if (count && count % 3 == 0)
            result = "," + result;
        result = std::to_string(n % 10) + result;
        n /= 10;
        count++;
    }
    return result;
}

Solver::Solver(const std::string& tile_str, int dim) : scan_count(0), dim(dim) {
    tiles = parse_tiles(tile_str);
}

std::vector<Tile> Solver::parse_tiles(const std::string& tile_str) {
    std::vector<Tile> result;
    std::stringstream ss(tile_str);
    std::string token;
    while (ss >> token) {
        result.emplace_back(token);
    }
    return result;
}

int Solver::calculate_cost(const std::vector<Tile>& t) {
    int cost = 0;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            int idx = i * dim + j;
            const Tile& tile = t[idx];

            if (i > 0 && tile.n != t[(i - 1) * dim + j].s) {
                cost++;
                scan_count++;
            }
            if (j > 0 && tile.w != t[i * dim + (j - 1)].e) {
                cost++;
                scan_count++;
            }
            if (i < dim - 1 && tile.s != t[(i + 1) * dim + j].n) {
                cost++;
                scan_count++;
            }
            if (j < dim - 1 && tile.e != t[i * dim + (j + 1)].w) {
                cost++;
                scan_count++;
            }
        }
    }
    return cost;
}

void Solver::transition(std::vector<Tile>& t) {
    int total = dim * dim;
    int i = rand() % total;
    int j = rand() % total;
    while (j == i) j = rand() % total;
    std::swap(t[i], t[j]);
}

double Solver::init_temperature(int samples, double eps) {
    double T1 = 0.0, T2 = 1e6, T = T2;
    std::vector<Tile> copy = tiles;

    while ((T2 - T1) > 1.0) {
        T = (T1 + T2) / 2.0;
        int accepted = 0;

        for (int k = 0; k < samples; ++k) {
            int a = rand() % (dim * dim);
            int b = rand() % (dim * dim);
            while (b == a) b = rand() % (dim * dim);

            int before = calculate_cost(copy);
            std::swap(copy[a], copy[b]);
            int after = calculate_cost(copy);
            int delta = after - before;

            if (delta <= 0 || std::exp(-delta / T) > 1.0 - eps) {
                accepted++;
            }

            std::swap(copy[a], copy[b]); // revert
        }

        if (accepted >= 0.98 * samples)
            T2 = T;
        else
            T1 = T;
    }
    return T;
}

std::string Solver::solve() {
    srand(time(0));
    std::vector<Tile> current = tiles;
    int cost = calculate_cost(current);
    double T = init_temperature();
    const double Tmin = 0.8;
    const double alpha = 0.999;

    std::mt19937 rng(rand());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    while (cost > 0) {
        std::vector<Tile> proposed = current;
        transition(proposed);
        int new_cost = calculate_cost(proposed);
        int delta = new_cost - cost;

        if (delta <= 0 || dist(rng) < std::exp(-delta / T)) {
            current = proposed;
            cost = new_cost;
        }

        T = std::max(T * alpha, Tmin);
    }

    std::cout << "Solution Found! Scanned: " 
              << format_number_with_commas(scan_count) 
              << " states." << std::endl;

    std::string result;
    for (int i = 0; i < dim * dim; ++i) {
        result += current[i].to_string();
        if (i != dim * dim - 1) result += " ";
    }
    return result;
}
