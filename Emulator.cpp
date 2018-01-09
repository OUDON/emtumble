#include "Emulator.hpp"

Emulator::Emulator(Board _board) : board(_board) {}

void Emulator::run(bool verbose)
{
    board.lever_pulled(BLUE);
    if (verbose) board.print();
    while (board.is_runnning()) {
        board.step();
        if (verbose) {
            std::cout << "---------------" << std::endl;
            board.print();
        }
    }
}

std::string Emulator::get_results()
{
    return board.get_results();
}
