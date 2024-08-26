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