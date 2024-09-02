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
#include "PlaceGrid.h"

class GroupUnitState {
public:

    GroupUnitState(int ind, PlaceGrid& pg);

    int getPFirstFin() { return placement.pmos[leftPdummy].nfin; }
    int getNFirstFin() { return placement.nmos[leftNdummy].nfin; }
    int getPLastFin() { 
        assert(width - rightPdummy - 1 >= 0);
        return placement.pmos[width - rightPdummy - 1].nfin;
    }
    int getNLastFin() {
        assert(width - rightNdummy - 1 >= 0);
        return placement.nmos[width - rightNdummy - 1].nfin;
    }

    // input values
    PlaceGrid placement;
    int index;
    int width;
    int leftPdummy, rightPdummy;
    int leftNdummy, rightNdummy;
    std::string leftPnet, rightPnet;
    std::string leftNnet, rightNnet;

    // assume no NONLY, PONLY groupunit

    // to be determined
    int prevBestState;
    int offset;

};


class DynamicGroupState {
public:
    DynamicGroupState() : hostIndex(-1), offset(-1), rightNoffset(-1), rightPoffset(-1), isFirst(false), enable(true) {}
    DynamicGroupState(int _ind, int _host, int _offset, bool _isfirst) : index(_ind), hostIndex(_host), offset(_offset), rightNoffset(-1), rightPoffset(-1), isFirst(_isfirst), enable(true) {}

    int index;
    int hostIndex;

    int offset;
    int rightNoffset, rightPoffset;
    int rightNfin, rightPfin;
    std::string rightNnet, rightPnet;

    std::vector<int> prevBestStates;

    bool isFirst;
    bool enable;

};

class PlaceGroupUnit {
public:

    PlaceGroupUnit(std::vector<PlaceGrid>& sols, bool reverse);
    
    std::vector<GroupUnitState> states;
    std::vector<DynamicGroupState> dstates;

    void initiateFirstGroupUnit();
    void resetGroupDstates();
    void disableRedundantDStates();
};
