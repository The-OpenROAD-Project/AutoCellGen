#include "../header/cdlParser.h"

#include <algorithm>

void cdlParser::parseCell(Cell &c, std::ifstream& ifs) {
	std::string line;
	while (getline(ifs, line)) {
		std::vector<std::string> tokens = split_by_space(line);
		if (tokens[0].front() == '*') continue;
		if (tokens[0] == ".ENDS") break;
		c.trans.emplace_back(tokens);
	}
	for (auto& tran : c.trans) {
		if (tran.type == transtype::NMOS) c.nmos.push_back(tran);
		else c.pmos.push_back(tran);

		if (std::find(c.nets.begin(), c.nets.end(), tran.source) == c.nets.end())
			c.nets.push_back(tran.source);
		
		if (std::find(c.nets.begin(), c.nets.end(), tran.drain) == c.nets.end())
			c.nets.push_back(tran.drain);
	}
}

void cdlParser::parse() {

    std::ifstream file(filepath);
    std::string line;

    while (getline(file, line)) {
        std::vector<std::string> tokens = split_by_space(line);
        if (tokens.size() < 1) continue;
        
        if (tokens[0] == ".SUBCKT") {
			Cell c(tokens);
			parseCell(c, file);
			lib.cells.push_back(c);
        }
    }
}

std::vector<std::string> cdlParser::split_by_space(std::string line) {

	std::vector<std::string> tokens;
	size_t prev = line.find_first_not_of(" ");
	size_t pos;

	while ((pos = line.find_first_of(" ", prev)) != std::string::npos) {
		if (pos > prev)
			tokens.push_back(line.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (prev < line.length())
		tokens.push_back(line.substr(prev, std::string::npos));

	return tokens;

}