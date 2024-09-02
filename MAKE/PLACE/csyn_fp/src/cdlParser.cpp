////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2024, Kyeonghyeon Baek, Sehyeon Chung, Handong Cho, 
// Hyunbae Seo, Kyu-myung Choi, and Taewhan Kim
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////

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
