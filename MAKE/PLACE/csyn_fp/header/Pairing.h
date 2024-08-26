#pragma once

#include "global.h"
#include "beol_data.h"
#include "setting.h"

class Pair {
public:
    Pair() {
        is_xc_pair = false;
    }

public:
    bool is_xc_pair;
    std::vector <Transistor> pmos, nmos;
};


class Pairer {
public:
    Pairer(Cell &_cell) : cell(_cell) {}

    void pairing();

    void grouping();
    void find_complement_net();
    void find_transmission_candidate();
    void pairing_cross_coupled();
    void pairing_transistors();


public:
    Cell &cell;

    int num_tran;
    std::vector<bool> ispaired;

    int num_group;
    std::vector<std::vector<int>> groups;

    std::vector<std::pair<std::string, std::string>> comp_net_list;    
    std::vector<std::tuple<int, int, int>> transmission_list; // PMOS index, NMOS index, shared net name, group index
    
    std::vector<Pair> pair_list;
    std::unordered_map<int, int> pairGroup;


};
