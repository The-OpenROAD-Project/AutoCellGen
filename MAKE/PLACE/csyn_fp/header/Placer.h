#pragma once

#include "global.h"
#include "beol_data.h"
#include "setting.h"
#include "PlaceUnit.h"
#include "PlaceGrid.h"
#include "PlaceGroupUnit.h"

#define MAX_OFFSET 9999

class Placer {
public:
    Placer();
//    Placer(Cell& c) : cell(c), min_width(9999) {}
//    Placer(Cell& c, int mw) : cell(c), min_width(mw) {}
    Placer(Cell& c, int mw=MAX_OFFSET) : cell(c), min_width(mw){}

    void run();
    void runSearchwithRelax();
    void runSearchOnly();

    void runEachGroup();


    // input variables
    Cell cell;
    int min_width; 
    int lower_bound; // can be changed during search

	std::string out_dir;

    // after pairing
    std::unordered_map<int, int> pairGroup; // pair index->group index
    int numGroup;
    //std::vector<std::pair<Transistor, Transistor>> pairs;
    std::vector<Pair> pairs;
    
    // after generatePlaceUnit
    std::vector<PlaceUnit> units;
    int numUnit;

    // after findSolution
    //std::vector<PlaceGrid> solutions;
    std::unordered_map<int, std::vector<PlaceGrid>> solutions;



    std::ofstream dbg;

    //void pairing(); // Transistor pairing, output : pairs
    void generatePlaceUnit();
    void findSolution(int curr, int prev, std::vector<int>& order, bool fix_bound);
    void backtrackSolution (int currIndex, std::vector<int> &dstates, std::vector<int> &order, int currOrder, int width);
    void printSolution(std::string outPath);
    void print_refinedSol(fs::path outPath);
    void refineSolution();
    //void addSolution(std::vector<DynamicState*> &dPtrList, std::vector<int> &order, int width);

    void calculateState (PlaceUnit& prev, PlaceUnit& curr);

}; 



