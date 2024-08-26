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