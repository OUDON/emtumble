#pragma once

#include <string>
#include "Board.hpp"

class Emulator {
    Board board;

public:
    Emulator(Board _board);
    void run(bool verbose);
    std::string get_results();
};
