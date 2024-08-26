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