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

#include "../header/PlaceUnit.h"

UnitState::UnitState(int _index, std::vector<int> nmos_v, std::vector<int> pmos_v, Transistor& nmos_t, Transistor& pmos_t) {
    index = _index;

    PlacedTrans nulltran("null", "null", "null", "null", 0);

    int nmos_size = static_cast<int>(nmos_v.size());
    int pmos_size = static_cast<int>(pmos_v.size());
    assert(nmos_size == pmos_size);

    size = nmos_size;

    for (int i = 0; i < nmos_size; i++) {
        int nfin = nmos_v[i];
        if (nfin == 0) {
            nmos.push_back(nulltran);
        }
        else if (nfin > 0) {
            nmos.emplace_back(nmos_t.name, nmos_t.source, nmos_t.gate, nmos_t.drain, nfin);
        }
        else {
            nmos.emplace_back(nmos_t.name, nmos_t.drain, nmos_t.gate, nmos_t.source, -nfin);
        }
    }
    for (int i = 0; i < pmos_size; i++) {
        int pfin = pmos_v[i];
        if (pfin == 0) {
            pmos.push_back(nulltran);
        }
        else if (pfin > 0) {
            pmos.emplace_back(pmos_t.name, pmos_t.source, pmos_t.gate, pmos_t.drain, pfin);
        }
        else {
            pmos.emplace_back(pmos_t.name, pmos_t.drain, pmos_t.gate, pmos_t.source, -pfin);
        }
    }

    leftNzero = 0;
    for (int i = 0; i < nmos_size; i++) {
        if (nmos_v[i] != 0) break;
        leftNzero++;
    }
    rightNzero = 0;
    for (int i = nmos_size - 1; i >= 0; i--) {
        if (nmos_v[i] != 0) break;
        rightNzero++;
    }
    if (leftNzero == nmos_size) leftNzero = 0;
    if (rightNzero == nmos_size) rightNzero = 0;


    leftPzero = 0;
    for (int i = 0; i < pmos_size; i++) {
        if (pmos_v[i] != 0) break;
        leftPzero++;
    }
    rightPzero = 0;
    for (int i = pmos_size - 1; i >= 0; i--) {
        if (pmos_v[i] != 0) break;
        rightPzero++;
    }
    if (leftPzero == pmos_size) leftPzero = 0;
    if (rightPzero == pmos_size) rightPzero = 0;

    NfirstFin = nmos[leftNzero].nfin;
    PfirstFin = pmos[leftPzero].nfin;
    NfirstFinHeight = 0;
    for (int i = leftNzero; i < nmos_size; i++) {
        if (NfirstFin == 0) break;
        if (nmos[i].nfin != NfirstFin) break;
        NfirstFinHeight++;
    }
    PfirstFinHeight = 0;
    for (int i = leftPzero; i < pmos_size; i++) {
        if (PfirstFin == 0) break;
        if (pmos[i].nfin != PfirstFin) break;
        PfirstFinHeight++;
    }

    NsecondFin = nmos[nmos_size - rightNzero - 1].nfin;
    if (NsecondFin == NfirstFin) {
        NsecondFin = 0;
        NsecondFinHeight = 0;
    }
    else {
        NsecondFinHeight = 0;
        for (int i = nmos_size - rightNzero - 1; i >= 0; i--) {
            if (nmos[i].nfin == NsecondFin) NsecondFinHeight++;
            else break;
        }
    }

    PsecondFin = pmos[pmos_size - rightPzero - 1].nfin;
    if (PsecondFin == PfirstFin) {
        PsecondFin = 0;
        PsecondFinHeight = 0;
    }
    else {
        PsecondFinHeight = 0;
        for (int i = pmos_size - rightPzero - 1; i >= 0; i--) {
            if (pmos[i].nfin == PsecondFin) PsecondFinHeight++;
            else break;
        }
    }

    // centerzero value issue when NONLY, PONLY?
    centerNzero = 0;
    for (int i = leftNzero; i < nmos_size - rightNzero; i++) {
        if (nmos[i].nfin == 0) centerNzero++;
    }
    centerPzero = 0;
    for (int i = leftPzero; i < pmos_size - rightPzero; i++) {
        if (pmos[i].nfin == 0) centerPzero++;
    }

    Nlength = NfirstFinHeight + NsecondFinHeight + centerNzero;
    Plength = PfirstFinHeight + PsecondFinHeight + centerPzero;

}

UnitState::UnitState (int _index, std::vector<PlacedTrans> _nmos, std::vector<PlacedTrans> _pmos) {
    index = _index;
    nmos = _nmos;
    pmos = _pmos;

    int nmos_size = static_cast<int>(nmos.size());
    int pmos_size = static_cast<int>(pmos.size());
    assert(nmos_size == pmos_size);

    size = nmos_size;

    leftNzero = 0;
    for (int i = 0; i < nmos_size; i++) {
        if (nmos[i].nfin != 0) break;
        leftNzero++;
    }
    rightNzero = 0;
    for (int i = nmos_size - 1; i >= 0; i--) {
        if (nmos[i].nfin != 0) break;
        rightNzero++;
    }
    if (leftNzero == nmos_size) leftNzero = 0;
    if (rightNzero == nmos_size) rightNzero = 0;


    leftPzero = 0;
    for (int i = 0; i < pmos_size; i++) {
        if (pmos[i].nfin != 0) break;
        leftPzero++;
    }
    rightPzero = 0;
    for (int i = pmos_size - 1; i >= 0; i--) {
        if (pmos[i].nfin != 0) break;
        rightPzero++;
    }
    if (leftPzero == pmos_size) leftPzero = 0;
    if (rightPzero == pmos_size) rightPzero = 0;

    NfirstFin = nmos[leftNzero].nfin;
    PfirstFin = pmos[leftPzero].nfin;
    NfirstFinHeight = 0;
    for (int i = leftNzero; i < nmos_size; i++) {
        if (NfirstFin == 0) break;
        if (nmos[i].nfin != NfirstFin) break;
        NfirstFinHeight++;
    }
    PfirstFinHeight = 0;
    for (int i = leftPzero; i < pmos_size; i++) {
        if (PfirstFin == 0) break;
        if (pmos[i].nfin != PfirstFin) break;
        PfirstFinHeight++;
    }

    NsecondFin = nmos[nmos_size - rightNzero - 1].nfin;
    if (NsecondFin == NfirstFin) {
        NsecondFin = 0;
        NsecondFinHeight = 0;
    }
    else {
        NsecondFinHeight = 0;
        for (int i = nmos_size - rightNzero - 1; i >= 0; i--) {
            if (nmos[i].nfin == NsecondFin) NsecondFinHeight++;
            else break;
        }
    }

    PsecondFin = pmos[pmos_size - rightPzero - 1].nfin;
    if (PsecondFin == PfirstFin) {
        PsecondFin = 0;
        PsecondFinHeight = 0;
    }
    else {
        PsecondFinHeight = 0;
        for (int i = pmos_size - rightPzero - 1; i >= 0; i--) {
            if (pmos[i].nfin == PsecondFin) PsecondFinHeight++;
            else break;
        }
    }

    // centerzero value issue when NONLY, PONLY?
    centerNzero = 0;
    for (int i = leftNzero; i < nmos_size - rightNzero; i++) {
        if (nmos[i].nfin == 0) centerNzero++;
    }
    centerPzero = 0;
    for (int i = leftPzero; i < pmos_size - rightPzero; i++) {
        if (pmos[i].nfin == 0) centerPzero++;
    }

    Nlength = NfirstFinHeight + NsecondFinHeight + centerNzero;
    Plength = PfirstFinHeight + PsecondFinHeight + centerPzero;


}

std::ostream& operator<<(std::ostream& os, const UnitState &us) {
    os << "State " << us.index << std::endl;
    os << "NMOS" << std::endl;
    for (auto ntran : us.nmos) {
        os << ntran.nfin << " ";
    }
    os << std::endl;
    os << "PMOS" << std::endl;
    for (auto ptran : us.pmos) {
        os << ptran.nfin << " ";
    }
    os << std::endl << "LeftNnet = " << us.getNLeftNet() << ", LeftPnet = " << us.getPLeftNet() << std::endl;
    os << std::endl;

    return os;
}

std::ostream& operator<<(std::ostream& os, const DynamicState &ds) {
    os << "DState " << ds.index << std::endl;

    os << "rightNnet = " << ds.rightNnet << ", rightPnet = " << ds.rightPnet << std::endl;
    os << "offset = " << ds.offset << std::endl;
    os << "rightNoffset = " << ds.rightNoffset << ", rightPoffset = " << ds.rightPoffset << std::endl;
    os << "rightNfin = " << ds.rightNfin << ", rightPfin = " << ds.rightPfin << std::endl;
    os << "N_OD = " << ds.N_OD << ", P_OD = " << ds.P_OD << std::endl;

    assert(ds.rightPfin >= 0);

    return os;
}

/*
PlaceUnit::PlaceUnit (Transistor t) {
    if (t.type == transtype::NMOS) {
        nmos = t;
        type = unitType::NONLY;

        Transistor p(transtype::PMOS);
        pmos = std::move(p);
    }
    else {
        pmos = t;
        type = unitType::PONLY;

        Transistor n(transtype::NMOS);
        nmos = std::move(n);
    }
}*/

PlaceUnit::PlaceUnit(Pair p) {
    pair = p;
    if (pair.nmos.size() > 0 && pair.pmos.size() > 0) {
        type = unitType::BOTH;
    }
    else if (pair.nmos.size() == 0) {
        type = unitType::PONLY;
    }
    else if (pair.pmos.size() == 0) {
        type = unitType::NONLY;
    }
    else std::cout << "Error!" << std::endl;
}

void PlaceUnit::generateStates() {

    if (type != unitType::PONLY) assert(pair.nmos.size() == 1);
    if (type != unitType::NONLY) assert(pair.pmos.size() == 1);

    std::cout << "Start generating states!" << std::endl;
    auto generateVector = [&] (std::vector<int> &v, std::vector<int> &vfirst, std::vector<int> &vsecond) {
        int numZero;
        v.clear();
        v.insert(v.end(), vfirst.begin(), vfirst.end());
        if (vfirst.back() * vsecond.front() < 0) numZero = setting.WidthDiffGap;
        else numZero = std::max(setting.WidthDiffGap, setting.NetDiffGap);
        
        if (numZero > 0) v.insert(v.end(), numZero, 0);
        v.insert(v.end(), vsecond.begin(), vsecond.end());
    };




    std::vector<std::vector<int>> nfinShapeSet;
    std::vector<std::vector<int>> pfinShapeSet;

    Transistor nmos, pmos;
    
    if (pair.nmos.size() > 0) {

        nmos = pair.nmos[0];

        // one fin height style
        for (int fin = setting.NMOSMaxAllowedFin; fin >= 1; fin--) {
            if (nmos.nfin < fin) continue;
            if (nmos.nfin % fin == 0) {
                std::vector<int> nfinShape(nmos.nfin / fin, fin);
                for (int i = 0; i < nfinShape.size(); i += 2) nfinShape[i] *= -1;
                nfinShapeSet.push_back(nfinShape);
                for (int i = 0; i < nfinShape.size(); ++i) nfinShape[i] *= -1;
                nfinShapeSet.push_back(nfinShape);

                if (setting.folding_style == "static") break;

            }
        }
        // two fin height style
        /*
        for (int bigFin = setting.MaxAllowedFin; bigFin > 1; bigFin--) {
            for (int smallFin = bigFin - 1; smallFin >= 1; smallFin--) {
                if (bigFin + smallFin > nmos.nfin) continue;
                for (int bigHeight = nmos.nfin / bigFin; bigHeight >= 1; bigHeight--) {
                    if ((nmos.nfin - bigFin * bigHeight) % smallFin == 0) {
                        int smallHeight = (nmos.nfin - bigFin * bigHeight) / smallFin;
                    
                        if (smallHeight <= 0) continue;

                        std::vector<int> vbig(bigHeight, bigFin);
                        std::vector<int> vsmall(smallHeight, smallFin);
                        for (int i = 0; i < vbig.size(); i += 2) vbig[i] *= -1;
                        for (int i = 0; i < vsmall.size(); i += 2) vsmall[i] *= -1;               

                        std::vector<int> v;
                        // case one : (-, -)
                        generateVector(v, vbig, vsmall);
                        nfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        nfinShapeSet.push_back(v);

                        // case two : (+, -)
                        for (int i = 0; i < vbig.size(); i++) vbig[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        nfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        nfinShapeSet.push_back(v);

                        // case three : (+, +)
                        for (int i = 0; i < vsmall.size(); i++) vsmall[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        nfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        nfinShapeSet.push_back(v);

                        // case four : (-, +)
                        for (int i = 0; i < vbig.size(); i++) vbig[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        nfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        nfinShapeSet.push_back(v);
                    
                        break;
                    }
                }
            }
        }
        */

        if (nfinShapeSet.size() > 0) {
            nMinLeg = 9999;
            assert(nfinShapeSet.size() > 0);
            for (const auto& nfinShape : nfinShapeSet) {
                if (nMinLeg > nfinShape.size())
                    nMinLeg = nfinShape.size();
            }

            // delete long sequence
            for (auto iter = nfinShapeSet.begin(); iter != nfinShapeSet.end(); ) {
                if (iter->size() > nMinLeg + std::max(setting.NetDiffGap, setting.WidthDiffGap)) {
                    iter = nfinShapeSet.erase(iter);
                }
                else ++iter;
            }
        }
        else nMinLeg = 0;
    
    }
    else nMinLeg = 0;


    if (pair.pmos.size() > 0) {

        pmos = pair.pmos[0];

        // one fin style
        for (int fin = setting.PMOSMaxAllowedFin; fin >= 1; fin--) {
            if (pmos.nfin < fin) continue;
            if (pmos.nfin % fin == 0) {
                std::vector<int> pfinShape(pmos.nfin / fin, fin);
                for (int i = 0; i < pfinShape.size(); i += 2) pfinShape[i] *= -1;
                pfinShapeSet.push_back(pfinShape);
                for (int i = 0; i < pfinShape.size(); ++i) pfinShape[i] *= -1;
                pfinShapeSet.push_back(pfinShape);

                if (setting.folding_style == "static") break;


            }



        }   
        // two fin style
        /*
        for (int bigFin = setting.MaxAllowedFin; bigFin > 1; bigFin--) {
            for (int smallFin = bigFin - 1; smallFin >= 1; smallFin--) {
                if (bigFin + smallFin > pmos.nfin) continue;
                for (int bigHeight = pmos.nfin / bigFin; bigHeight >= 1; bigHeight--) {
                    if ((pmos.nfin - bigFin * bigHeight) % smallFin == 0) {
                        int smallHeight = (pmos.nfin - bigFin * bigHeight) / smallFin;
                    
                        if (smallHeight <= 0) continue;

                        std::vector<int> vbig(bigHeight, bigFin);
                        std::vector<int> vsmall(smallHeight, smallFin);
                        for (int i = 0; i < vbig.size(); i += 2) vbig[i] *= -1;
                        for (int i = 0; i < vsmall.size(); i += 2) vsmall[i] *= -1;               

                        std::vector<int> v;
                        // case one : (-, -)
                        generateVector(v, vbig, vsmall);
                        pfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        pfinShapeSet.push_back(v);

                        // case two : (+, -)
                        for (int i = 0; i < vbig.size(); i++) vbig[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        pfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        pfinShapeSet.push_back(v);

                        // case three : (+, +)
                        for (int i = 0; i < vsmall.size(); i++) vsmall[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        pfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        pfinShapeSet.push_back(v);

                        // case four : (-, +)
                        for (int i = 0; i < vbig.size(); i++) vbig[i] *= -1;
                        generateVector(v, vbig, vsmall);
                        pfinShapeSet.push_back(v);
                        generateVector(v, vsmall, vbig);
                        pfinShapeSet.push_back(v);
                        
                        break;
                    }
                }
            }
        }
        */

        if (pfinShapeSet.size() > 0) {
            pMinLeg = 9999;
            assert(pfinShapeSet.size() > 0);
            for (const auto& pfinShape : pfinShapeSet) {
                if (pMinLeg > pfinShape.size())
                    pMinLeg = pfinShape.size();
            }

            // delete long sequence
            for (auto iter = pfinShapeSet.begin(); iter != pfinShapeSet.end(); ) {
                if (iter->size() > pMinLeg + std::max(setting.NetDiffGap, setting.WidthDiffGap)) {
                    iter = pfinShapeSet.erase(iter);
                }
                else ++iter;
            }
        }
        else pMinLeg = 0;
    
    }
    else pMinLeg = 0;


    // collect
    if (type == unitType::BOTH) {
        int index = 0;
        for (const auto& nfinShape : nfinShapeSet) {
            for (const auto& pfinShape : pfinShapeSet) {
                int nSize = nfinShape.size();
                int pSize = pfinShape.size();

    //          std::cout << "nsize : " << nSize << ", psize : " << pSize << std::endl;

                if (nSize > pSize) {
                    auto nmos_v = nfinShape;
                    for (int i = 0; i <= nSize - pSize; i++) {
                        auto pmos_v = pfinShape;
                        pmos_v.insert(pmos_v.begin(), i, 0);
                        pmos_v.insert(pmos_v.end(), (nSize - pSize - i), 0);
                        states.emplace_back(index++, nmos_v, pmos_v, nmos, pmos);
                    }
                }
                else if (nSize < pSize) {
                    auto pmos_v = pfinShape;
                    for (int i = 0; i <= pSize - nSize; i++) {
                        auto nmos_v = nfinShape;
                        nmos_v.insert(nmos_v.begin(), i, 0);
                        nmos_v.insert(nmos_v.end(), (pSize - nSize - i), 0);
                        states.emplace_back(index++, nmos_v, pmos_v, nmos, pmos);
                    }
                }
                else {
                    auto nmos_v = nfinShape;
                    auto pmos_v = pfinShape;
                    states.emplace_back(index++, nmos_v, pmos_v, nmos, pmos);
                }
            }
        }
    }
    else if (type == unitType::NONLY) {
        int index = 0;
        for (auto& nfinShape : nfinShapeSet) {
            auto nmos_v = nfinShape;
            std::vector<int> pmos_v(nmos_v.size(), 0);
            states.emplace_back(index++, nmos_v, pmos_v, nmos, pmos);
        }
    }
    else {
        int index = 0;
        for (auto& pfinShape : pfinShapeSet) {
            auto pmos_v = pfinShape;
            std::vector<int> nmos_v(pmos_v.size(), 0);
            states.emplace_back(index++, nmos_v, pmos_v, nmos, pmos);
        }
    }

}

void PlaceUnit::generateStates_xc() {
    assert(pair.nmos.size() == 2);
    assert(pair.pmos.size() == 2);

    auto& pmos1 = pair.pmos[0];
    auto& nmos1 = pair.nmos[0];
    auto& pmos2 = pair.pmos[1];
    auto& nmos2 = pair.nmos[1];

    auto find_common_net = [](std::string f1, std::string f2, std::string s1, std::string s2) {
        std::vector<std::string> common_nets;
        if ((f1 == s1 && f2 == s2) || (f1 == s2 && f2 == s1)) {
            common_nets.push_back(f1);
            common_nets.push_back(f2);
        }
        else {
            if (f1 == s1 || f1 == s2) common_nets.push_back(f1);
            else if (f2 == s1 || f2 == s2) common_nets.push_back(f2);
        }
        return common_nets;
    };

    auto common1 = find_common_net(pmos1.source, pmos1.drain, nmos1.source, nmos1.drain);
    auto common2 = find_common_net(pmos2.source, pmos2.drain, nmos2.source, nmos2.drain);

    std::string common_net;
    for (auto common_net1 : common1) {
        for (auto common_net2 : common2) {
            if (common_net1 == common_net2) {
                common_net = common_net1;
                break;
            }
        }
    }

    std::string pmos1_other_net = (pmos1.source == common_net) ? (pmos1.drain) : (pmos1.source);
    std::string nmos1_other_net = (nmos1.source == common_net) ? (nmos1.drain) : (nmos1.source);
    std::string pmos2_other_net = (pmos2.source == common_net) ? (pmos2.drain) : (pmos2.source);
    std::string nmos2_other_net = (nmos2.source == common_net) ? (nmos2.drain) : (nmos2.source);

    PlacedTrans nulltran("null", "null", "null", "null", 0); // name, left, gate, right, nfin

    int index = 0;        
    std::vector<PlacedTrans> _nmos, _pmos;

    if (setting.XC == 2) {
        // case 1    
        _pmos.clear();
        _nmos.clear();

        _pmos.emplace_back(pmos1.name, pmos1_other_net, pmos1.gate, common_net, pmos1.nfin);
        if((pmos1.nfin!=pmos2.nfin)||(nmos1.nfin!=nmos2.nfin)){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos2.name, common_net, pmos2.gate, pmos2_other_net, pmos2.nfin);
        
        _nmos.emplace_back(nmos1.name, nmos1_other_net, nmos1.gate, common_net, nmos1.nfin);
        if((pmos1.nfin!=pmos2.nfin)||(nmos1.nfin!=nmos2.nfin)){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos2.name, common_net, nmos2.gate, nmos2_other_net, nmos2.nfin);
        
        states.emplace_back(index++, _nmos, _pmos);

        // Case 2
        _pmos.clear();
        _nmos.clear();

        _pmos.emplace_back(pmos2.name, pmos2_other_net, pmos2.gate, common_net, pmos2.nfin);
        if((pmos1.nfin!=pmos2.nfin)||(nmos1.nfin!=nmos2.nfin)){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos1.name, common_net, pmos1.gate, pmos1_other_net, pmos1.nfin);
        
        _nmos.emplace_back(nmos2.name, nmos2_other_net, nmos2.gate, common_net, nmos2.nfin);
        if((pmos1.nfin!=pmos2.nfin)||(nmos1.nfin!=nmos2.nfin)){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos1.name, common_net, nmos1.gate, nmos1_other_net, nmos1.nfin);
        
        states.emplace_back(index++, _nmos, _pmos);

        nMinLeg = 2;
        pMinLeg = 2;
        if((pmos1.nfin!=pmos2.nfin)||(nmos1.nfin!=nmos2.nfin)){
            nMinLeg+=setting.WidthDiffGap;
            pMinLeg+=setting.WidthDiffGap;
        }

    }
    else if (setting.XC == 3) {
        // case 1
        _pmos.clear();
        _nmos.clear();
        
        _pmos.emplace_back(pmos1.name, pmos1_other_net, pmos1.gate, common_net, pmos1.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos2.name, common_net, pmos2.gate, pmos2_other_net, pmos2.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.push_back(nulltran);

        _nmos.push_back(nulltran);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos1.name, nmos1_other_net, nmos1.gate, common_net, nmos1.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos2.name, common_net, nmos2.gate, nmos2_other_net, nmos2.nfin);

        states.emplace_back(index++, _nmos, _pmos);

        // case 2
        _pmos.clear();
        _nmos.clear();
                
        _pmos.push_back(nulltran);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos1.name, pmos1_other_net, pmos1.gate, common_net, pmos1.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos2.name, common_net, pmos2.gate, pmos2_other_net, pmos2.nfin);

        _nmos.emplace_back(nmos1.name, nmos1_other_net, nmos1.gate, common_net, nmos1.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos2.name, common_net, nmos2.gate, nmos2_other_net, nmos2.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.push_back(nulltran);

        states.emplace_back(index++, _nmos, _pmos);

        // case 2
        _pmos.clear();
        _nmos.clear();

        _pmos.emplace_back(pmos2.name, pmos2_other_net, pmos2.gate, common_net, pmos2.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos1.name, common_net, pmos1.gate, pmos1_other_net, pmos1.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.push_back(nulltran);

        _nmos.push_back(nulltran);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos2.name, nmos2_other_net, nmos2.gate, common_net, nmos2.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos1.name, common_net, nmos1.gate, nmos1_other_net, nmos1.nfin);
        
        states.emplace_back(index++, _nmos, _pmos);

        // Case 4
        _pmos.clear();
        _nmos.clear();

        _pmos.push_back(nulltran);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos2.name, pmos2_other_net, pmos2.gate, common_net, pmos2.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _pmos.push_back(nulltran);
            }
        }
        _pmos.emplace_back(pmos1.name, common_net, pmos1.gate, pmos1_other_net, pmos1.nfin);
        
        _nmos.emplace_back(nmos2.name, nmos2_other_net, nmos2.gate, common_net, nmos2.nfin);
        if(nmos1.nfin!=nmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.emplace_back(nmos1.name, common_net, nmos1.gate, nmos1_other_net, nmos1.nfin);
        if(pmos1.nfin!=pmos2.nfin){
            for(int i=0; i<setting.WidthDiffGap; ++i){
                _nmos.push_back(nulltran);
            }
        }
        _nmos.push_back(nulltran);

        states.emplace_back(index++, _nmos, _pmos);

        nMinLeg = 3;
        pMinLeg = 3;
        if(pmos1.nfin!=pmos2.nfin){
            nMinLeg+=setting.WidthDiffGap;
            pMinLeg+=setting.WidthDiffGap;
        }
        if(nmos1.nfin!=nmos2.nfin){
            nMinLeg+=setting.WidthDiffGap;
            pMinLeg+=setting.WidthDiffGap;
        }
    }


}

void PlaceUnit::initiateFirstUnit() {
    int ind = 0;
    for (auto& state : states) {
        DynamicState dstate(ind++, state.index, 0, true);
        if (type == unitType::BOTH) {
            dstate.rightNnet = state.getNRightNet();
            dstate.rightPnet = state.getPRightNet();
            dstate.rightNfin = state.getNLastFin();
            dstate.rightPfin = state.getPLastFin();
            assert(dstate.rightNfin >= 0);
            assert(dstate.rightPfin >= 0);
            dstate.rightNoffset = state.nmos.size() - state.rightNzero - 1;            
            dstate.rightPoffset = state.pmos.size() - state.rightPzero - 1;
            if (state.NsecondFin != 0) {
                if (state.NfirstFin > state.NsecondFin) {
                    dstate.N_OD = (state.NsecondFinHeight + state.centerNzero > setting.MinODjog) ? 0 : (state.NsecondFinHeight + state.centerNzero);
                }
                else dstate.N_OD = 0;
            }
            else dstate.N_OD = 0;
            if (state.PsecondFin != 0) {
                if (state.PfirstFin > state.PsecondFin) {
                    dstate.P_OD = (state.PsecondFinHeight + state.centerPzero > setting.MinODjog) ? 0 : (state.PsecondFinHeight + state.centerPzero);
                }
                else dstate.P_OD = 0;
            }
            else dstate.P_OD = 0;

        }
        else if (type == unitType::PONLY) {
            dstate.rightPnet = state.getPRightNet();
            dstate.rightPfin = state.getPLastFin();
            dstate.rightPoffset = state.pmos.size() - state.rightPzero - 1;
            dstate.N_OD = 0;
            if (state.PsecondFin != 0) {
                if (state.PfirstFin > state.PsecondFin) {
                    dstate.P_OD = (state.PsecondFinHeight + state.centerPzero > setting.MinODjog) ? 0 : (state.PsecondFinHeight + state.centerPzero);
                }
                else dstate.P_OD = 0;
            }
            else dstate.P_OD = 0;


        }
        else if (type == unitType::NONLY) {
            dstate.rightNnet = state.getNRightNet();
            dstate.rightNoffset = state.nmos.size() - state.rightNzero - 1;
            dstate.rightNfin = state.getNLastFin();
            dstate.P_OD = 0;
            if (state.NsecondFin != 0) {
                if (state.NfirstFin > state.NsecondFin) {
                    dstate.N_OD = (state.NsecondFinHeight + state.centerNzero > setting.MinODjog) ? 0 : (state.NsecondFinHeight + state.centerNzero);
                }
                else dstate.N_OD = 0;
            }
            else dstate.N_OD = 0;
        }
        dstates.push_back(std::move(dstate));

    }
}

void PlaceUnit::resetDStates() {
    dstates.clear();
}

void PlaceUnit::disableRedundantDStates() {
    int numDState = dstates.size();
    for (int i = 0; i < numDState; i++) {
        DynamicState& dstateA = dstates[i];
        if (!dstateA.enable) continue;
        for (int j = 0; j < numDState; j++) {
            if (i == j) continue;
            DynamicState& dstateB = dstates[j];
            if (!dstateB.enable) continue;
            if (setting.NetDiffGap > 0 && dstateA.rightNnet != dstateB.rightNnet) continue;
            if (setting.NetDiffGap > 0 && dstateA.rightPnet != dstateB.rightPnet) continue;
            if (setting.WidthDiffGap > 0 && dstateA.rightNfin != dstateB.rightNfin) continue;
            if (setting.WidthDiffGap > 0 && dstateA.rightPfin != dstateB.rightPfin) continue;
            if (setting.MinODjog > 0 && dstateA.N_OD != dstateB.N_OD) continue;
            if (setting.MinODjog > 0 && dstateA.P_OD != dstateB.P_OD) continue;

            if (dstateA.rightPoffset > dstateB.rightPoffset && dstateA.rightNoffset > dstateB.rightPoffset) {
                dstateA.enable = false;
                break;
            }
            if (dstateA.rightPoffset < dstateB.rightPoffset && dstateA.rightNoffset < dstateB.rightNoffset) {
                dstateB.enable = false;
            }
        }
    }

}
