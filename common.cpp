#include "common.hpp"
#include <QFile>
#include <QTextStream>

std::vector<std::string> common::read_file(std::string file_name)
{
    std::ifstream ifs(file_name.c_str());
    if (ifs.fail()) return std::vector<std::string>();
    std::string str;
    std::vector<std::string> res;
    while (getline(ifs, str)) {
        res.push_back(str);
    }
    return res;
}

std::vector<std::string> common::read_file_qt(std::string file_name)
{
    std::vector<std::string> res;
    QFile file(file_name.c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return res;

    QTextStream in(&file);
    while (!in.atEnd()) {
        std::string line = in.readLine().toStdString();
        res.push_back(line);
    }
    return res;
}
