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

#include "../header/PlaceGroupUnit.h"

GroupUnitState::GroupUnitState(int ind, PlaceGrid& pg) {
    index = ind;
    width = pg.cellWidth;
    placement = pg;

    auto& nmos = pg.nmos;
    leftNdummy = 0;
    for (int i = 0; i < nmos.size(); i++) {
        if (nmos[i].name != "dummy") {
            leftNnet = nmos[i].left;
            break;
        } 
        leftNdummy++;
    }
    rightNdummy = 0;
    for (int i = nmos.size() - 1; i >= 0; i--) {
        if (nmos[i].name != "dummy") {
            rightNnet = nmos[i].right;
            break;
        } 
        rightNdummy++;
    }

    auto& pmos = pg.pmos;
    leftPdummy = 0;
    for (int i = 0; i < pmos.size(); i++) {
        if (pmos[i].name != "dummy") {
            leftPnet = pmos[i].left;
            break;
        } 
        leftPdummy++;
    }
    rightPdummy = 0;
    for (int i = pmos.size() - 1; i >= 0; i--) {
        if (pmos[i].name != "dummy") {
            rightPnet = pmos[i].right;
            break;
        } 
        rightPdummy++;
    }

    offset = -1;

}

PlaceGroupUnit::PlaceGroupUnit(std::vector<PlaceGrid>& sols, bool reverse) {
    int index = 0;
    for (auto& sol : sols) {
        states.emplace_back(index++, sol);

        if (!reverse) continue;

        PlaceGrid temp = sol;
        
        for (int i = 0; i < temp.cellWidth; i++) {
            temp.nmos[i] = sol.nmos[temp.cellWidth - i - 1];
            std::swap(temp.nmos[i].left, temp.nmos[i].right);
            temp.pmos[i] = sol.pmos[temp.cellWidth - i - 1];
            std::swap(temp.pmos[i].left, temp.pmos[i].right);
        }
        
        
        // ****save temp if the number of unit is greater than 1
        states.emplace_back(index++, temp);

    }
}

void PlaceGroupUnit::initiateFirstGroupUnit() {
    int ind = 0;
    for (auto& state : states) {
        DynamicGroupState dstate(ind++, state.index, 0, true);
        dstate.rightNnet = state.rightNnet;
        dstate.rightPnet = state.rightPnet;
        dstate.rightNoffset = dstate.offset + state.width - state.rightNdummy - 1;
        dstate.rightPoffset = dstate.offset + state.width - state.rightPdummy - 1;
        dstate.rightNfin = state.placement.nmos[dstate.rightNoffset].nfin;
        dstate.rightPfin = state.placement.pmos[dstate.rightPoffset].nfin;
        dstates.push_back(std::move(dstate));
    }
}

void PlaceGroupUnit::resetGroupDstates() {
    dstates.clear();
}

void PlaceGroupUnit::disableRedundantDStates() {
    int numDState = dstates.size();
    for (int i = 0; i < numDState; i++) {
        DynamicGroupState& dstateA = dstates[i];
        if (!dstateA.enable) continue;
        for (int j = 0; j < numDState; j++) {
            if (i == j) continue;
            DynamicGroupState& dstateB = dstates[j];
            if (!dstateB.enable) continue;
            if (setting.NetDiffGap > 0 && dstateA.rightNnet != dstateB.rightNnet) continue;
            if (setting.NetDiffGap > 0 && dstateA.rightPnet != dstateB.rightPnet) continue;
            if (setting.WidthDiffGap > 0 && dstateA.rightNfin != dstateB.rightNfin) continue;
            if (setting.WidthDiffGap > 0 && dstateA.rightPfin != dstateB.rightPfin) continue;

            if (dstateA.rightPoffset > dstateB.rightPoffset && dstateA.rightNoffset > dstateB.rightPoffset) {
                dstateA.enable = false;
                break;
            }
            if (dstateA.rightPoffset < dstateB.rightPoffset && dstateA.rightNoffset < dstateB.rightNoffset) {
                dstateB.enable = false;
            }            


            /*int xp_a = dstateA.rightPoffset;
            int xn_a = dstateA.rightNoffset;
            int xp_b = dstateB.rightPoffset;
            int xn_b = dstateB.rightNoffset;

            int l1_a = std::max(xp_a, xn_a);
            int l1_b = std::max(xp_b + std::max(xn_a - xp_a, 0), xn_b + std::max(xp_a - xn_a, 0));
            int l2_b = std::max(xp_b, xn_b);
            int l2_a = std::max(xp_a + std::max(xn_b - xp_b, 0), xn_a + std::max(xp_b - xn_b, 0));

            if ((l1_a >= l1_b && l2_a >= l2_b) && !(l1_a == l1_b && l2_a == l2_b)) {
            //if (l1_a >= l1_b && l2_a >= l2_b) {
                //std::cout << "xp_a, xn_a : " << xp_a << ", " << xn_a << ", xp_b, xn_b : " << xp_b << ", " << xn_b << std::endl;
                //std::cout << "l1_a, l1_b : " << l1_a << ", " << l1_b << ", l2_a, l2_b : " << l2_a << ", " << l2_b << std::endl;
                //std::cout << "State A is disabled" << std::endl;
                dstateA.enable = false;
                break;
            }
            if ((l1_a <= l1_b && l2_a <= l2_b) && !(l1_a == l1_b && l2_a == l2_b)) {
            //if (l1_a <= l1_b && l2_a <= l2_b) {
                //std::cout << "xp_a, xn_a : " << xp_a << ", " << xn_a << ", xp_b, xn_b : " << xp_b << ", " << xn_b << std::endl;
                //std::cout << "l1_a, l1_b : " << l1_a << ", " << l1_b << ", l2_a, l2_b : " << l2_a << ", " << l2_b << std::endl;
                //std::cout << "State B is disabled" << std::endl;
                dstateB.enable = false;
            }
            */
        }
    }
/*
    int count = 0;
    for (const auto& state : states) {
        if (state.enable) count++;
    }
    std::cout << "Unit " << nmos.gate << ", Enable states : " << numState << " -> " << count << std::endl;
*/
}
