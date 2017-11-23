#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include "Board.hpp"
#include "Emulator.hpp"

std::vector<std::string> read_file(std::string file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.fail()) return std::vector<std::string>();
    std::string str;
    std::vector<std::string> res;
    while (getline(ifs, str)) {
        res.push_back(str);
        std::cerr << str << std::endl;
    }
    return res;
}

int main(int argc, char *argv[])
{    
    if (argc != 2) {
        std::cout << "Usage: emtumble filename" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    Board board(read_file(filename));
    Emulator emu(board);

    emu.run(true);

    std::cout << "===============" << std::endl;
    std::cout << emu.get_results() << std::endl;
}
