#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "Board.hpp"
#include "Emulator.hpp"
#include "common.hpp"

#include "GUI.hpp"

int main(int argc, char *argv[])
{    
    if (argc != 2 && argc != 3) {
        std::cout << "Usage: emtumble filename [--gui | --cli]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    Board board(common::read_file(filename));
    Emulator emu(board);

    if (argc == 2 || std::string(argv[2]) == "--gui") {
        GUI::get_instance().start(&argc, argv);
    } else {
        emu.run(true);
        std::cout << "===============" << std::endl;
        std::cout << emu.get_results() << std::endl;
    }
}
