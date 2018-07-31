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
    if (argc != 1 && argc != 3) {
        std::cout << "Usage: emtumble [--cli filename]" << std::endl;
        return EXIT_FAILURE;
    }

    if (argc == 1) {
        GUI::get_instance().start(&argc, argv);
    } else {
        if (std::string(argv[1]) == "--cli") {
            std::string filename = argv[2];
            std::vector<std::string> board_str = common::read_file(filename);
            Board board(board_str);
            Emulator emu(board);
            emu.run(true);
            std::cout << "===============" << std::endl;
            std::cout << emu.get_results() << std::endl;
        } else {
            std::cerr << "Invalid command line arugments" << std::endl;
            return EXIT_FAILURE;
        }
    }
}
