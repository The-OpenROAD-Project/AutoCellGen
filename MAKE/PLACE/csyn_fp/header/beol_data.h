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

enum class transtype {NMOS, PMOS};

class Point {
public:
    Point () : y(-1), x(-1) {}
    Point (int y_, int x_) : y(y_), x(x_) {}

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

public:
    int x, y;

};


class PlacedTrans {
public:

    PlacedTrans(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin)
    : name(_name), left(_left), gate(_gate), right(_right), nfin(_nfin) {}

    void set(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin);

    bool operator==(const PlacedTrans &ot) const;
    bool operator!=(const PlacedTrans &ot) const;


    std::string name, left, gate, right;
    int nfin;
};


class Transistor {
public:
    Transistor() { name = "null"; }
    Transistor(transtype t) : name("null"), source("null"), drain("null"), gate("null"), contact("null"), type(t), width(0), length(0), nfin(0) {}
    Transistor(const std::vector<std::string>& tokens);

    friend std::ostream& operator<<(std::ostream& os, const Transistor& t);

    std::string name;
    std::string source, drain, gate, contact;
    transtype type;
    double width, length;
    int nfin;
};

class Cell {
public:

    Cell() {}
    Cell(const std::vector<std::string>& tokens);

    friend std::ostream& operator<<(std::ostream& os, const Cell& c);

    int GetTransNum() const { return trans.size(); }

    std::string name;
    std::vector<std::string> IOnets;
    std::vector<std::string> nets;
    std::vector<Transistor> trans;
    std::vector<Transistor> nmos, pmos;

};

class Library {
public:
    friend std::ostream& operator<<(std::ostream& os, const Library& l);

    std::vector<Cell> cells;
};
