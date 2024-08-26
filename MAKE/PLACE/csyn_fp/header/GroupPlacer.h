#pragma once

#include "beol_data.h"
#include "PlaceGroupUnit.h"
#include "Placer.h"
#include "Pairing.h"

class GroupPlacer {
public:

    GroupPlacer(Cell& c, int mw=9999) : cell(c), min_width(mw) {}

    void run();
    void runSearchwithRelax();

    // input variables
    Cell cell;
    int min_width;   
    int lower_bound; // can be changed during search

	std::string out_dir;


    // after pairing
    std::unordered_map<int, int> pairGroup; // pair index->group index
    int numGroup;
    std::vector<Pair> pairs;

    std::vector<PlaceGroupUnit> groupUnits; // group units
    int numGroupUnit;

    // final solutions
    //std::vector<PlaceGrid> solutions;
    std::unordered_map<int, std::vector<PlaceGrid>> solutions;


    //void pairing();
    void findGroupSolution(int curr, int prev, std::vector<int>& order, bool fix_bound);
    void calculateGroupState (PlaceGroupUnit& prev, PlaceGroupUnit& curr);
    void printSolution(std::string outPath);
    void backtrackGroupSolution(int currIndex, std::vector<int> &dstateList, std::vector<int> &order, int currOrder, int width);

    void print_refinedSol(fs::path outPath);



};
