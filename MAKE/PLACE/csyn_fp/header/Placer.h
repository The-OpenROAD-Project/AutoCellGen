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



