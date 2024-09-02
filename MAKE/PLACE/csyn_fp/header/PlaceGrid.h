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

#pragma once

#include "global.h"
#include "setting.h"
#include "beol_data.h"

class OutputTrans {
public:

    OutputTrans(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin)
    : name(_name), left(_left), gate(_gate), right(_right), nfin(_nfin) {}

    void set(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin);

    bool operator==(const OutputTrans &ot) const;
    bool operator!=(const OutputTrans &ot) const;


    std::string name, left, gate, right;
    int nfin;
};


class PlaceGrid {
public:
    PlaceGrid () {}

    PlaceGrid(std::vector<OutputTrans> _nmos, std::vector<OutputTrans> _pmos, int _cw)
    : nmos(_nmos), pmos(_pmos), cellWidth(_cw) {}


    bool operator==(const PlaceGrid &pg) const;
    bool operator!=(const PlaceGrid &pg) const;

    std::vector<OutputTrans> nmos, pmos;
    std::vector<std::vector<double>> h_net_den, v_net_den; // 5 * (2 * #PMOS + 1)
    std::vector<double> hor_cong, ver_cong;


    std::unordered_map<std::string, std::vector<std::vector<Point>>> contact_list;
    
    int cellWidth;

    double nor_hpwl, max_h_grid, max_v_grid, max_h_column, max_v_row, max_h_row, max_v_column;


    double cost;

    void print_place (Cell& cell, fs::path outPath, int num);
    void find_contact_list ();
    void cal_density ();
    void cal_cost();

};
