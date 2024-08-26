#pragma once

#include "global.h"
#include "beol_data.h"

class cdlParser {
public:
    cdlParser(Library &l, std::string fp) : lib(l), filepath(fp) {}
    cdlParser(Library &l, fs::path fp) : lib(l), filepath(fp.string()) {}

    void parse();
    std::vector<std::string> split_by_space(std::string line);

private:
    Library &lib;
    std::string filepath;

    void parseCell(Cell &c, std::ifstream& ifs);

};
