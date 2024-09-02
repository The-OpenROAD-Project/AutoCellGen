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
#include "Pairing.h"

class UnitState {
public:

    UnitState(int _index, std::vector<int> nmos_v, std::vector<int> pmos_v, Transistor& nmos, Transistor& pmos);
    UnitState(int _index, std::vector<PlacedTrans> _nmos, std::vector<PlacedTrans> _pmos);
    //UnitState(int _index, std::vector<int> _nmos, std::vector<int> _pmos);
    //UnitState(int _index, std::vector<int> _nmos, std::vector<int> _pmos, bool nf, bool pf);
    //UnitState(int _nleg, int _pleg, std::vector<int> _nmos, std::vector<int> _pmos, bool nf, bool pf)
    //: offset(-1), nleg(_nleg), pleg(_pleg), nmos(_nmos), pmos(_pmos), nflip(nf), pflip(pf) {}


    friend std::ostream& operator<<(std::ostream& os, const UnitState &us);

    int getSize() const { return size; }
    int getNFirstFin() const { return nmos[leftNzero].nfin; }
    int getNLastFin() const { return nmos[size - rightNzero - 1].nfin; }
    int getPFirstFin() const { return pmos[leftPzero].nfin; }
    int getPLastFin() const { return pmos[size - rightPzero - 1].nfin; }
    int getNumNlegs() const { return size - leftNzero - rightNzero; }
    int getNumPlegs() const { return size - leftPzero - rightPzero; }
    std::string getNLeftNet() const { return nmos[leftNzero].left; }
    std::string getPLeftNet() const { return pmos[leftPzero].left; }
    std::string getNRightNet() const { return nmos[size - rightNzero - 1].right; }
    std::string getPRightNet() const { return pmos[size - rightPzero - 1].right; }

    // calculated when the state generated

    int index;                      // state index
    int size;
    /*
    int leftNzero, rightNzero, centerNzero;      // the number of zeros in each side of NFET
    int leftPzero, rightPzero, centerPzero;      // the number of zeros in each side of PFET
    std::vector<int> nmos, pmos;    // NFET, PFET fin info
    int NfirstFin, NsecondFin, NfirstFinHeight, NsecondFinHeight;
    int PfirstFin, PsecondFin, PfirstFinHeight, PsecondFinHeight;
    */
    int leftNzero, rightNzero, centerNzero;
    int leftPzero, rightPzero, centerPzero;
    std::vector<PlacedTrans> nmos, pmos;
    
    int NfirstFin, NfirstFinHeight, NsecondFin, NsecondFinHeight;
    int PfirstFin, PfirstFinHeight, PsecondFin, PsecondFinHeight;
    int Nlength, Plength;


};

class DynamicState {
public:

    DynamicState() : hostIndex(-1), offset(-1), rightNoffset(-1), rightPoffset(-1), isFirst(false), enable(true), rightNfin(0), rightPfin(0){}
    DynamicState(int _ind, int _host, int _offset, bool _isfirst) : index(_ind), hostIndex(_host), offset(_offset), rightNoffset(-1), rightPoffset(-1), isFirst(_isfirst), enable(true), rightNfin(0), rightPfin(0) {}

    DynamicState(int _index, int _hostIndex, int _offset, int _rightNoffset, int _rightPoffset, 
                 int _rightNfin, int _rightPfin, int _N_OD, int _P_OD, std::string _rightNnet, std::string _rightPnet, 
                 std::vector<int> _prevBestStates, bool _isFirst, bool _enable)
    : index(_index), hostIndex(_hostIndex), offset(_offset), rightNoffset(_rightNoffset), rightPoffset(_rightPoffset), rightNfin(_rightNfin), rightPfin(_rightPfin),
      N_OD(_N_OD), P_OD(_P_OD), rightNnet(_rightNnet), rightPnet(_rightPnet), prevBestStates(_prevBestStates), isFirst(_isFirst), enable(_enable) {}

    friend std::ostream& operator<<(std::ostream& os, const DynamicState &ds);

    int index;
    //UnitState *host;

    int hostIndex;                    // host state's index
    int offset;
    int rightNoffset, rightPoffset;
    int rightNfin, rightPfin;
    int N_OD, P_OD;                   // distance (rightmost <-> left wall)
    std::string rightNnet, rightPnet;
    std::vector<int> prevBestStates;

    bool isFirst;
    bool enable;
    
};


class PlaceUnit {
public:
    //PlaceUnit(Transistor t);
    //PlaceUnit(Transistor n, Transistor p) : nmos(n), pmos(p), type(unitType::BOTH) {}
    //PlaceUnit(const PlaceUnit& u) : nmos(u.nmos), pmos(u.pmos), nMinLeg(u.nMinLeg), pMinLeg(u.pMinLeg), type(u.type), states(u.states) {}

    PlaceUnit(Pair p);

    void generateStates();
    void generateStates_xc();
//    void setStatesOffset(int off);
    void initiateFirstUnit();          
    void resetDStates();
    void disableRedundantDStates();
/*
    std::string getNLeftnet(int flipped) const { return (flipped > 0) ? nmos.source : nmos.drain; }
    std::string getNRightnet(int flipped) const { return (flipped > 0) ? nmos.drain : nmos.source; }
    std::string getPLeftnet(int flipped) const { return (flipped > 0) ? pmos.source : pmos.drain; }
    std::string getPRightnet(int flipped) const { return (flipped > 0) ? pmos.drain : pmos.source; }
*/
    //Transistor nmos, pmos;
    
    Pair pair;
    int nMinLeg, pMinLeg;
    unitType type;
    std::vector<UnitState> states;
    std::vector<DynamicState> dstates;

};
