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

#include "../header/beol_data.h"


std::ostream& operator<< (std::ostream& os, const Transistor& t) {
	os << t.name << " " << t.source << " " << t.gate << " " << t.drain << " " << t.contact << " ";
	if (t.type == transtype::NMOS) os << "nmos_rvt ";
	else if (t.type == transtype::PMOS) os << "pmos_rvt ";
	os << "w=" << t.width << "n l=" << t.length << "n nfin=" << t.nfin; 
	return os;
}

std::ostream& operator<< (std::ostream& os, const Cell& c) {
	os << ".SUBCKT " << c.name;
	for (const auto& n : c.nets) os << " " << n;
	os << std::endl;
	for (const auto& t : c.trans) os << t << std::endl;
	os << ".ENDS" << std::endl;
	return os;
}

std::ostream& operator<< (std::ostream& os, const Library& l) {
	for (const auto& c : l.cells) os << c << std::endl;
	return os;
}

void PlacedTrans::set(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin)
{
    name = _name;
    left = _left;
    gate = _gate;
    right = _right;
    nfin = _nfin;
}

bool PlacedTrans::operator==(const PlacedTrans &ot) const {
    if (this->gate == ot.gate && this->left == ot.left && this->right == ot.right && this->nfin == ot.nfin)
        return true;
    else return false;
}

bool PlacedTrans::operator!=(const PlacedTrans &ot) const {
    if (!(*this == ot)) return true;
    else return true;
}


Transistor::Transistor(const std::vector<std::string>& tokens) {

	name = tokens[0];
	source = tokens[1];
	gate = tokens[2];
	drain = tokens[3];
	contact = tokens[4];

	if (tokens[5] == "nmos_rvt" || tokens[5] == "nfet") type = transtype::NMOS;
	else if (tokens[5] == "pmos_rvt" || tokens[5] == "pfet") type = transtype::PMOS;
	else std::cout << "Type Error!" << std::endl;
/*
	width = stod(tokens[6].substr(2, tokens[6].size() - 1));
	length = stod(tokens[7].substr(2, tokens[7].size() - 1));

	nfin = stoi(tokens[8].substr(5));
	if (tokens.size() > 9) {
		int nfgr = stoi(tokens[9].substr(5));
		nfin *= nfgr;
	}
*/
	for (auto iter = tokens.begin() + 6; iter != tokens.end(); ++iter) {
		if (iter->substr(0, 2) == "W=") {
			//std::cout << "Width" << std::endl;
			width = stod(iter->substr(2, iter->size() - 1));
		}
		else if (iter->substr(0, 2) == "L=") {
			//std::cout << "Length" << std::endl;
			length = stod(iter->substr(2, iter->size() - 1));
		}
		else if (iter->substr(0, 4) == "nfin") {
			nfin = stoi(iter->substr(5));
		}
		else if (iter->substr(0, 4) == "nfgr") {
			int nfgr = stoi(iter->substr(5));
			nfin *= nfgr;
		}
	}


}

Cell::Cell(const std::vector<std::string>& tokens) {
	name = tokens[1];
	for (auto it = tokens.begin() + 2; it != tokens.end(); it++) {
		IOnets.push_back(*it);
	}
}
