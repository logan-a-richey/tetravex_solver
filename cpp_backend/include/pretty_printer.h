// pretty_printer.h

#ifndef PRETTYPRINTER_H
#define PRETTYPRINTER_H

#include <string>
#include <vector>

class PrettyPrinter {
public:
    PrettyPrinter(int dim);
    static void print_board(const std::string& flat_string);

private:
    int dim;
    std::string repeat(const std::string& s, int times);
    void pretty_print_board(const std::string& flat_string);
};

#endif // PRETTYPRINTER_H

