#include "common.hpp"

std::vector<std::string> common::read_file(std::string file_name)
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
