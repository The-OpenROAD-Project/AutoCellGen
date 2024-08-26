#include "../header/Placer.h"

Placer::Placer() {
    min_width = 9999;
}

void Placer::run() {

    Pairer pairer(cell);
    pairer.pairing();

    // need to modify (copy to reference)
    pairGroup = pairer.pairGroup;
    pairs = pairer.pair_list;

    generatePlaceUnit();

    numUnit = units.size();
    std::cout << "test_NumUnit : " << numUnit << std::endl;

    for (const auto& unit : units) {
        if (unit.pair.is_xc_pair) std::cout << "XC pair, #States : " << unit.states.size() << std::endl;
        else {
            if (unit.pair.nmos.size() > 0) {
                std::cout << "Gate : " << unit.pair.nmos[0].gate << ", NMOS : " << unit.pair.nmos[0].name;
            }
            if (unit.pair.pmos.size() > 0) {
                std::cout << ", PMOS : " << unit.pair.pmos[0].name;
            }
            std::cout << ", States : " << unit.states.size() << std::endl;
        }
    }

    dbg.open("debug.txt");

    runSearchwithRelax();

	std::cout << cell.name << std::endl;
    // refinement stage
    if (setting.refine_sol) {
        std::cout << "Do refinement!" << std::endl;
        refineSolution();
    }
    
	std::cout << cell.name << std::endl;

	//std::string filePath = fs::current_path() / fs::path("input/7.5Tdataset/placement/" + cell.name + ".txt");
	std::string filePath = out_dir + "/" + cell.name + ".txt";
    std::cout<<"filePath: "<<filePath<<std::endl;
    printSolution(filePath);
  
    fs::path outPath = fs::current_path() / fs::path("placements") / fs::path(cell.name);
    fs::create_directories(outPath);
    print_refinedSol(outPath);

    dbg.close();

}

void Placer::runSearchwithRelax() {
    numUnit = units.size();

    std::vector<int> order(numUnit, -1);
    lower_bound = MAX_OFFSET;
    findSolution(0, -1, order, false);
    min_width = lower_bound;

    if (setting.relaxation > 0) {
        lower_bound = min_width + setting.relaxation;
        findSolution(0, -1, order, true);
    }

}

void Placer::runSearchOnly() {
    numUnit = units.size();
    std::cout << "test2_NumUnit : " << numUnit << std::endl;

    for (const auto& unit : units) {
        if (unit.pair.is_xc_pair) std::cout << "XC pair, #States : " << unit.states.size() << std::endl;
        else std::cout << "Gate : " << unit.pair.nmos[0].gate << ", NMOS : " << unit.pair.nmos[0].name << ", PMOS : " << unit.pair.pmos[0].name << ", States : " << unit.states.size() << std::endl;
    }

    runSearchwithRelax();

}

void Placer::runEachGroup() {
    generatePlaceUnit();
    runSearchwithRelax();
    if (setting.refine_sol) refineSolution();
}


void Placer::generatePlaceUnit() {
    std::cout << "Start generating placement unit!" << std::endl;
    for (const auto& pair : pairs) {
        /*
        if (pair.second.name == "null") {
//          cout << get<0>(pair).name << endl;
            PlaceUnit unit(pair.first);
            unit.generateStates();
            units.push_back(unit);
        }
        else {
            PlaceUnit unit(pair.first, pair.second);
            unit.generateStates();
            units.push_back(unit);
        }*/
        PlaceUnit unit(pair);
        if (pair.is_xc_pair) unit.generateStates_xc();
        else unit.generateStates();
        units.push_back(unit);
    }

}

void Placer::findSolution(int curr, int prev, std::vector<int>& order, bool fix_bound) {

    // removing symetric solution
    
    if (setting.remove_sym) {
        if (curr >= (numUnit + 1) / 2) {
            if (numUnit % 2 == 0) {
                if (order[0] < 0) return;
            }
            else {
                if (order[0] < 0) return;
                if (order[0] == (numUnit + 1) / 2 && order[1] < 0) return;
            }
        }
    }

    // branch and bound
    
    if (setting.branch_bound) {
        if (lower_bound < MAX_OFFSET && prev != -1) {
            
            int nMinRemain = 0;
            int pMinRemain = 0;
            for (int i = 0; i < numUnit; i++) {
                if (order[i] < 0) {
                    nMinRemain += units[i].nMinLeg;
                    pMinRemain += units[i].pMinLeg;
                }
            }

            int count = 0;
            for (auto& dstate : units[prev].dstates) {
                if (!dstate.enable) continue;
                count++;
                int nLowerBound = nMinRemain + dstate.rightNoffset;
                int pLowerBound = pMinRemain + dstate.rightPoffset;
                if (std::max(pLowerBound, nLowerBound) > lower_bound) {
                    dstate.enable = false;
                    count--;
                }
            }
            if (count == 0) { // All dynamic states are disabled
                return;
            }
            
        }
    }

    // reach the leaf node, find solution
    if (curr >= numUnit) {
        for (int i = 0; i < numUnit; i++) {
            if (order[i] < 0) {
                std::cout << "Error : Unexplored units!" << std::endl;
                return;
            }
        }

        for (const auto& dstate : units[prev].dstates) {

            int dstateWidth = std::max(dstate.rightNoffset, dstate.rightPoffset) + 1;
            if (dstateWidth > lower_bound) continue;
            //std::cout << "offset = " << dstate.offset << ", rightNoffset = " << dstate.rightNoffset << ", rightPoffset = " << dstate.rightPoffset << ", DstateWidth = " << dstateWidth << std::endl;

            if (!fix_bound) {
                if (dstateWidth < lower_bound) {
                    solutions[lower_bound].clear();
                    solutions.erase(lower_bound);
                    lower_bound = dstateWidth;
                    std::cout << "Min width is updated to " << lower_bound << std::endl;
                }
            }
            //if (solutions[lower_bound].size() >= setting.numSolutions) continue; // is necessary?

            //std::cout << "Start backtracking solution" << std::endl;

            numUnit = units.size();
            std::vector<int> sol(numUnit, -1);
            sol[numUnit - 1] = dstate.index;
            
            backtrackSolution(dstate.index, sol, order, numUnit - 1, dstateWidth);

        
        }
        return;
    }

    for (int i = 0; i < numUnit; i++) {
        if (order[i] < 0) {
            if (curr == 0) {
                order[i] = 0;

                units[i].initiateFirstUnit();       // generate first unit of dstates
                //units[i].disableRedundantDStates(); // disable redundant dstates
            
                findSolution(curr + 1, i, order, fix_bound);
                
                order[i] = -1;
                units[i].resetDStates(); // MAX_OFFSET
            }
            else {
                order[i] = curr;
                calculateState(units[prev], units[i]);

                findSolution(curr + 1, i, order, fix_bound);

                units[i].resetDStates();
                order[i] = -1;
            }
        }
    }
}

void Placer::backtrackSolution(int currIndex, std::vector<int> &dstateList, std::vector<int> &order, int currOrder, int width)  {
    dstateList[currOrder] = currIndex;

    auto findUnitIndex = [&](int unit_order) {
        for (int i = 0; i < numUnit; i++) 
            if (order[i] == unit_order)
                return i;
        std::cout << "Can't find unit!" << std::endl;
        return -1;
    };

    std::ofstream out("output.txt");
    if (currOrder == 0) {
        OutputTrans dummy("dummy", "dummy", "dummy", "dummy", 0);
        std::vector<OutputTrans> nSol(width, dummy);
        std::vector<OutputTrans> pSol(width, dummy);

        out << "width : " << width << std::endl;

        for (int i = 0; i < dstateList.size(); i++) {
            assert(i < order.size());
            assert(findUnitIndex(i) < units.size());
            const PlaceUnit &unit = units[findUnitIndex(i)];

            assert(dstateList[i] < unit.dstates.size());
            const DynamicState &dstate = unit.dstates[dstateList[i]];


            assert(dstate.hostIndex < unit.states.size());
            const UnitState &state = unit.states[dstate.hostIndex];
            
            out << "Unit " << i << std::endl;
            out << dstate << std::endl;
            out << state << std::endl;

            for (int x = 0; x < state.nmos.size(); x++) {
                int nfin = state.nmos[x].nfin;
                if (nfin != 0) {
                    assert(dstate.offset + x < nSol.size());
                    nSol[dstate.offset + x].set(state.nmos[x].name, state.nmos[x].left, state.nmos[x].gate, state.nmos[x].right, state.nmos[x].nfin);
                }
            }

            for (int x = 0; x < state.pmos.size(); x++) {
                int pfin = state.pmos[x].nfin;

                if (pfin != 0) {
                    assert(dstate.offset + x < pSol.size());
                    pSol[dstate.offset + x].set(state.pmos[x].name, state.pmos[x].left, state.pmos[x].gate, state.pmos[x].right, state.pmos[x].nfin);
                }
            }


        }

        PlaceGrid tempSolution(std::move(nSol), std::move(pSol), width);

        // Count the number of steps
        int num_step = 0;
        int size = tempSolution.nmos.size();
        for (int i = 0; i < size - 1; i++) {
            if (tempSolution.nmos[i].nfin != 0 && tempSolution.nmos[i + 1].nfin != 0 && tempSolution.nmos[i].nfin != tempSolution.nmos[i + 1].nfin) num_step++;
            if (tempSolution.pmos[i].nfin != 0 && tempSolution.pmos[i + 1].nfin != 0 && tempSolution.pmos[i].nfin != tempSolution.pmos[i + 1].nfin) num_step++;
            if (num_step > setting.MaxStep) break;
        }
        if (num_step <= setting.MaxStep) {
            // check if there exists the same solution
            bool isSame = false;


            for (auto& solution : solutions[width]) {
                if (solution.cellWidth != tempSolution.cellWidth) {
                    continue;
                }
                bool curSame = true;
                for (int i = 0; i < tempSolution.cellWidth; i++) {
                    if ((tempSolution.nmos[i].gate != solution.nmos[i].gate) || (tempSolution.nmos[i].left != solution.nmos[i].left) || (tempSolution.nmos[i].right != solution.nmos[i].right) || (tempSolution.nmos[i].nfin != solution.nmos[i].nfin)) {
                        curSame = false;
                        break;
                    } 
                    if ((tempSolution.pmos[i].gate != solution.pmos[i].gate) || (tempSolution.pmos[i].left != solution.pmos[i].left) || (tempSolution.pmos[i].right != solution.pmos[i].right) || (tempSolution.pmos[i].nfin != solution.pmos[i].nfin)) {
                        curSame = false;
                        break;
                    } 
                }
                if (curSame) {
                    isSame = true;
                    break;
                }
            }


           //if (!isSame) solutions.push_back(std::move(tempSolution));
            if (!isSame) {

                auto& w_solutions = solutions[width];

                tempSolution.cal_cost();
                if (w_solutions.size() == 0) w_solutions.push_back(std::move(tempSolution));
                else if (tempSolution.cost < w_solutions[w_solutions.size() - 1].cost) {
                    // Add curr_solution to solution set
                    int i;
                    for (i = 0; i < w_solutions.size(); i++) {
                        if (w_solutions[i].cost > tempSolution.cost) break;
                    }

                    w_solutions.insert(w_solutions.begin() + i, std::move(tempSolution));
                    if (w_solutions.size() > setting.numSolutions) w_solutions.erase(w_solutions.end() - 1);
                    /*
                    for (int i = 0; i < w_solutions.size(); i++) {
                        std::cout << w_solutions[i].cost << " ";
                    }
                    std::cout << std::endl;
                    */
                }
                else if (tempSolution.cost == w_solutions[w_solutions.size() - 1].cost) {
                    if (w_solutions.size() < setting.numSolutions) w_solutions.push_back(std::move(tempSolution));
                }
            }
        
        }

        dstateList[currOrder] = -1;
        return;

    }

    int unitIndex = findUnitIndex(currOrder);
    for (auto prevDstateIndex : units[unitIndex].dstates[currIndex].prevBestStates) {
        backtrackSolution(prevDstateIndex, dstateList, order, currOrder - 1, width);
    }
    
    dstateList[currOrder] = -1;
}


void Placer::printSolution(std::string outPath) {

    for (int width = min_width; width <= min_width + setting.relaxation; width++) {    
        std::cout<<"print soultion!!!!!"<<std::endl;
        std::string out_path = outPath.substr(0, outPath.length() - 4) + "_w" + std::to_string(width + 2) + ".txt";
        std::ofstream out(out_path);
        if (solutions.find(width) != solutions.end()) {
            int counter = 1;
            std::cout << "The number of solutions of width " << width << " : " << solutions[width].size() << std::endl;
            //out << "The number of solutions of width " << width << " : " << solutions[width].size() << std::endl;
            for (const auto& solution : solutions[width]) {
                out << "-------- Solution " << counter++ << " --------" << std::endl;
                for (int i = 0; i < solution.cellWidth; i++) {
                    out << "[Column " << i + 1 << "]" << std::endl;
                    out << "NMOS : " << solution.nmos[i].name << "(" << solution.nmos[i].nfin << ") [" << solution.nmos[i].left << " " << solution.nmos[i].gate << " " << solution.nmos[i].right << "], ";
                    out << "PMOS : " << solution.pmos[i].name << "(" << solution.pmos[i].nfin << ") [" << solution.pmos[i].left << " " << solution.pmos[i].gate << " " << solution.pmos[i].right << "]" << std::endl;
                }
                out << std::endl;
                //if (counter >= 10) break;
            }            
        }
        out.close();

    }
}

void Placer::print_refinedSol(fs::path outPath) {

    auto out_path = outPath.string();
    int num = 0;
    for (auto& solution : solutions[min_width]) {
        solution.print_place(cell, out_path, num++);
    }
    
    std::string all_path = out_path + "/total_sol";
    std::ofstream all_out(all_path);

    num = 0;
    for (auto& solution : solutions[min_width]) {

        std::vector<std::string> p_net_order, n_net_order;
        std::vector<int> p_fin_order, n_fin_order;

        all_out << "[Solution " << num++ << "]" << std::endl;
        // PMOS
        for (int i = 0; i < solution.cellWidth; i++) {
            // Left diffusion
            if (i == 0) p_net_order.push_back(solution.pmos[i].left);
            else {
                auto left_tran_net = solution.pmos[i - 1].right;
                auto cur_tran_net = solution.pmos[i].left;
                if (left_tran_net == "dummy" && cur_tran_net == "dummy") p_net_order.push_back("NULL");
                else if (left_tran_net != "dummy" && cur_tran_net == "dummy") p_net_order.push_back(left_tran_net);
                else if (left_tran_net == "dummy" && cur_tran_net != "dummy") p_net_order.push_back(cur_tran_net);
                else p_net_order.push_back(left_tran_net);
            }

            // GATE
            if (solution.pmos[i].gate == "dummy") {
                p_net_order.push_back("NULL");
                p_fin_order.push_back(0);
            } 
            else {
                p_net_order.push_back(solution.pmos[i].gate);
                p_fin_order.push_back(solution.pmos[i].nfin);
            }

            // Right diffusion
            if (i == solution.cellWidth - 1) {
                if (solution.pmos[i].right == "dummy") p_net_order.push_back("NULL");
                else p_net_order.push_back(solution.pmos[i].right);
            }
        }
        // NMOS
        for (int i = 0; i < solution.cellWidth; i++) {
            // Left diffusion
            if (i == 0) n_net_order.push_back(solution.nmos[i].left);
            else {
                auto left_tran_net = solution.nmos[i - 1].right;
                auto cur_tran_net = solution.nmos[i].left;
                if (left_tran_net == "dummy" && cur_tran_net == "dummy") n_net_order.push_back("NULL");
                else if (left_tran_net != "dummy" && cur_tran_net == "dummy") n_net_order.push_back(left_tran_net);
                else if (left_tran_net == "dummy" && cur_tran_net != "dummy") n_net_order.push_back(cur_tran_net);
                else n_net_order.push_back(left_tran_net);
            }

            // GATE
            if (solution.nmos[i].gate == "dummy") {
                n_net_order.push_back("NULL");
                n_fin_order.push_back(0);
            } 
            else {
                n_net_order.push_back(solution.nmos[i].gate);
                n_fin_order.push_back(solution.nmos[i].nfin);
            }

            // Right diffusion
            if (i == solution.cellWidth - 1) {
                if (solution.nmos[i].right == "dummy") n_net_order.push_back("NULL");
                else n_net_order.push_back(solution.nmos[i].right);
            }
        }

        int space;
        // Print PMOS
        for (int i = 0; i < solution.cellWidth; i++) {
            // Diffusion
            all_out << p_net_order[i * 2] << " ";
            space = n_net_order[i * 2].length() - p_net_order[i * 2].length();
            if (space > 0) for (int k = 0; k < space; k++) all_out << " ";

            // Gate
            all_out << "(" << p_net_order[i * 2 + 1] << "(" << p_fin_order[i] << ")) ";
            space = n_net_order[i * 2 + 1].length() - p_net_order[i * 2 + 1].length();
            if (space > 0) for (int k = 0; k < space; k++) all_out << " ";

            if (i == solution.cellWidth - 1) {
                all_out << p_net_order[i * 2 + 2];
            }
        }
        all_out << std::endl;
        // Print NMOS
        for (int i = 0; i < solution.cellWidth; i++) {
            // Diffusion
            all_out << n_net_order[i * 2] << " ";
            space = p_net_order[i * 2].length() - n_net_order[i * 2].length();
            if (space > 0) for (int k = 0; k < space; k++) all_out << " ";

            // Gate
            all_out << "(" << n_net_order[i * 2 + 1] << "(" << n_fin_order[i] << ")) ";
            space = p_net_order[i * 2 + 1].length() - n_net_order[i * 2 + 1].length();
            if (space > 0) for (int k = 0; k < space; k++) all_out << " ";

            if (i == solution.cellWidth - 1) {
                all_out << n_net_order[i * 2 + 2];
            }
        }
        all_out << std::endl << std::endl;
    }
    all_out.close();

}

void Placer::refineSolution() {
    for (auto& sol : solutions[min_width]) {
        // nmos, pmos common dummy or length extended exists?
        int isDummy = 0;
        for (const auto& n : sol.nmos) {
            if (n.name == "dummy") {
                isDummy++;
                break;
            }
        }
        for (const auto& p : sol.pmos) {
            if (p.name == "dummy") {
                isDummy++;
                break;
            }
        }
        //if (isDummy < 2) continue;
        
        std::unordered_map<std::string, int> nlegs, plegs;
        for (const auto& n : sol.nmos) {
            if (n.name == "dummy") continue;
            if (nlegs.find(n.name) == nlegs.end()) nlegs[n.name] = 1;
            else nlegs[n.name]++;
        }
        for (const auto& p : sol.pmos) {
            if (p.name == "dummy") continue;
            if (plegs.find(p.name) == plegs.end()) plegs[p.name] = 1;
            else plegs[p.name]++;
        }
        auto getLegs = [&units = units] (std::string name, transtype type) {
            for (const auto &unit : units) {
                if (type == transtype::NMOS) {
                    if (unit.pair.nmos.size() == 1 && unit.pair.nmos[0].name == name)
                        return unit.nMinLeg;
                }
                else {
                    if (unit.pair.pmos.size() == 1 && unit.pair.pmos[0].name == name)
                        return unit.pMinLeg;
                }
            }
            return 999;
        };
        bool isMin = true;
        for (auto& nleg : nlegs) {
            if (getLegs(nleg.first, transtype::NMOS) < nleg.second) {
                isMin = false;
                break;
            }
        }
        for (auto& pleg : plegs) {
            if (getLegs(pleg.first, transtype::PMOS) < pleg.second) {
                isMin = false;
                break;
            }
        }
        if (!isMin || (isMin && isDummy > 0)) {

            // At this point, the solution can be optimized
            // Let's find better solution by dividing placement units

            std::cout << "Solution can be optimized!" << std::endl;

            // find solution by dividing fets with even number of fingers
            Placer p;
            p.min_width = min_width - 1;
            //p.min_width = MAX_OFFSET;

            for (auto& unit : units) {
                /*
                if (unit.nmos.gate == "clkn" || unit.nmos.gate == "clkb" || unit.nmos.gate == "cki" || unit.nmos.gate == "ncki" || unit.nmos.gate == "BCLK" || unit.nmos.gate == "NCLK") {
                    PlaceUnit temp1(unit.nmos);
                    PlaceUnit temp2(unit.pmos);
                    
                    temp1.generateStates();
                    temp2.generateStates();
                    p.units.push_back(std::move(temp1));
                    p.units.push_back(std::move(temp2));
                }*/
                if (unit.nMinLeg % 2 == 0 && unit.pMinLeg % 2 == 0) {
                    PlaceUnit temp = unit;
                    temp.pair.nmos[0].nfin /= 2;
                    temp.pair.pmos[0].nfin /= 2;
                    temp.nMinLeg /= 2;
                    temp.pMinLeg /= 2;
                    temp.states.clear();
                    temp.generateStates();
                    p.units.push_back(temp);
                    p.units.push_back(temp);
                }
                else p.units.push_back(unit);                
            }
            
            std::cout << "The number of units : " << p.units.size() << std::endl;

            for (const auto& unit : units) {
                if (unit.pair.is_xc_pair) std::cout << "XC pair, #States : " << unit.states.size() << std::endl;
                else std::cout << "Gate : " << unit.pair.nmos[0].gate << ", NMOS : " << unit.pair.nmos[0].name << ", PMOS : " << unit.pair.pmos[0].name << ", States : " << unit.states.size() << std::endl;
            }
            std::cout << "Start width = " << p.min_width << std::endl;

            p.runSearchOnly();

            // At this point, coarse refinement is adopted
            if (p.solutions.size() > 0) {
                std::cout << "Find " << p.solutions.size() << " solutions with size " << p.min_width << std::endl;
                min_width = p.min_width;
                solutions = std::move(p.solutions);
                break;
            }
            else {
                std::cout << "Cannot Find better solutions.." << std::endl;
                break;
            }
        }
    }
}


void Placer::calculateState(PlaceUnit& prev, PlaceUnit& curr) {
    int dindex = 0;
    if (curr.type == unitType::BOTH) {

        for (auto& currState : curr.states) {
            // store best states
            std::vector<std::vector<int>> imsiPrevBestStates;
            imsiPrevBestStates.clear();
            imsiPrevBestStates.resize((setting.MinODjog + 1) * (setting.MinODjog + 1));

            std::vector<int> minOffset ((setting.MinODjog + 1) * (setting.MinODjog + 1), MAX_OFFSET);

            for (const auto& prevDstate : prev.dstates) {

                if (!prevDstate.enable) continue;
                //dbg << currState << prevDstate << std::endl;

                int DiffGap;

                // Calculate P offset
                int Poffset, curr_remainP, PBaseOffset;

                PBaseOffset = prevDstate.rightPoffset + 1 - currState.leftPzero;

                // Net difference
                int NetGap = 0;
                if (!prevDstate.rightPnet.empty() && prevDstate.rightPnet != currState.getPLeftNet()) NetGap = setting.NetDiffGap;
                else NetGap = 0;

                // Fin difference
                int FinGap = 0;
                assert(currState.PfirstFin > 0);
                assert(currState.PfirstFinHeight > 0);
                if (prevDstate.rightPfin > 0 && prevDstate.rightPfin != currState.getPFirstFin()) FinGap = setting.WidthDiffGap;
                else FinGap = 0;

                // Min OD difference
                int ODGap = 0;
                if (currState.PsecondFin > 0 && currState.PfirstFin < currState.PsecondFin) { // case 1
                    if (prevDstate.rightPfin < currState.PfirstFin) {        // Case 1-1
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else if (prevDstate.rightPfin == currState.PfirstFin) { // Case 1-2
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD - currState.PfirstFinHeight - currState.centerPzero > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD - currState.PfirstFinHeight - currState.centerPzero) : 0; 
                    }
                    else {   // Case 1-3
                        ODGap = (setting.MinODjog + 1 - currState.PfirstFinHeight - currState.centerPzero > 0) ? (setting.MinODjog + 1 - currState.PfirstFinHeight - currState.centerPzero) : 0;
                    }
                }
                else if (currState.PsecondFin > 0 && currState.PfirstFin > currState.PsecondFin) {
                    if (currState.PfirstFin > prevDstate.rightPfin) {       // Case 2-1
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else ODGap = 0;     // Case 2-2
                }
                else if (currState.PfirstFin > 0) {   // Case 3 (one kind of fins)
                    assert(currState.PsecondFin == 0);
                    if (currState.PfirstFin > prevDstate.rightPfin) {
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else {
                        ODGap = 0;
                    }
                }
                DiffGap = std::max(std::max(NetGap, FinGap), ODGap);
                if (setting.avoid_gatecut) DiffGap = std::max(DiffGap, currState.leftPzero);

                Poffset = PBaseOffset + DiffGap;
                if (Poffset <= 0) Poffset = 0;

                NetGap = 0;
                FinGap = 0;
                ODGap = 0;
                DiffGap = 0;

                // Calculate N offset
                int Noffset;
                int NBaseOffset = prevDstate.rightNoffset + 1 - currState.leftNzero;

                // Net difference
                if (!prevDstate.rightNnet.empty() && prevDstate.rightNnet != currState.getNLeftNet()) NetGap = setting.NetDiffGap;
                else NetGap = 0;

                // Fin difference
                assert(currState.NfirstFin > 0);
                assert(currState.NfirstFinHeight > 0);
                if (prevDstate.rightNfin > 0 && prevDstate.rightNfin != currState.getNFirstFin()) FinGap = setting.WidthDiffGap;
                else FinGap = 0;

                // Min OD difference
                if (currState.NsecondFin > 0 && currState.NfirstFin < currState.NsecondFin) { // case 1
                    if (prevDstate.rightNfin < currState.NfirstFin) {        // Case 1-1
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else if (prevDstate.rightNfin == currState.NfirstFin) { // Case 1-2
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD - currState.NfirstFinHeight - currState.centerNzero > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD - currState.NfirstFinHeight - currState.centerNzero) : 0; 
                    }
                    else {   // Case 1-3
                        ODGap = (setting.MinODjog + 1 - currState.NfirstFinHeight - currState.centerNzero > 0) ? (setting.MinODjog + 1 - currState.NfirstFinHeight - currState.centerNzero) : 0;
                    }
                }
                else if (currState.NsecondFin > 0 && currState.NfirstFin > currState.NsecondFin) {
                    if (currState.NfirstFin > prevDstate.rightNfin) {       // Case 2-1
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else ODGap = 0;     // Case 2-2
                }
                else if (currState.NfirstFin > 0) {   // Case 3 (one kind of fins)
                    assert(currState.NsecondFin == 0);
                    if (currState.NfirstFin > prevDstate.rightNfin) {
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else {
                        ODGap = 0;
                    }
                }
                DiffGap = std::max(std::max(NetGap, FinGap), ODGap);
                if (setting.avoid_gatecut) DiffGap = std::max(DiffGap, currState.leftNzero);

                Noffset = NBaseOffset + DiffGap;
                if (Noffset <= 0) Noffset = 0;

                int currOffset = std::max(Poffset, Noffset);

                // Calculate New_N_OD, New_P_OD
                int new_N_OD, new_P_OD;

                int p_gap = currOffset + currState.leftPzero - prevDstate.rightPoffset - 1;
                if (currState.PsecondFin > 0 && currState.PfirstFin < currState.PsecondFin) new_P_OD = 0;
                else if (currState.PsecondFin > 0 && currState.PfirstFin > currState.PsecondFin) {
                    new_P_OD = (currState.centerPzero + currState.PsecondFinHeight > setting.MinODjog) ? 0 : (currState.centerPzero + currState.PsecondFinHeight);
                }
                else {
                    if (prevDstate.rightPfin < currState.PfirstFin) new_P_OD = 0;
                    else if (prevDstate.rightPfin == currState.PfirstFin) {
                        if (prevDstate.P_OD == 0) new_P_OD = 0;
                        else new_P_OD = (prevDstate.P_OD + p_gap + currState.PfirstFinHeight > setting.MinODjog) ? 0 : (prevDstate.P_OD + p_gap + currState.PfirstFinHeight);
                    }
                    else new_P_OD = (p_gap + currState.PfirstFinHeight > setting.MinODjog) ? 0 : (p_gap + currState.PfirstFinHeight);
                }

                int n_gap = currOffset + currState.leftNzero - prevDstate.rightNoffset - 1;
                if (currState.NsecondFin > 0 && currState.NfirstFin < currState.NsecondFin) new_N_OD = 0;
                else if (currState.NsecondFin > 0 && currState.NfirstFin > currState.NsecondFin) {
                    new_N_OD = (currState.centerNzero + currState.NsecondFinHeight > setting.MinODjog) ? 0 : (currState.centerNzero + currState.NsecondFinHeight);
                }
                else {
                    if (prevDstate.rightNfin < currState.NfirstFin) new_N_OD = 0;
                    else if (prevDstate.rightNfin == currState.NfirstFin) {
                        if (prevDstate.N_OD == 0) new_N_OD = 0;
                        else new_N_OD = (prevDstate.N_OD + n_gap + currState.NfirstFinHeight > setting.MinODjog) ? 0 : (prevDstate.N_OD + n_gap + currState.NfirstFinHeight);
                    }
                    else new_N_OD = (n_gap + currState.NfirstFinHeight > setting.MinODjog) ? 0 : (n_gap + currState.NfirstFinHeight);
                }

                //break;
                int key = new_P_OD * (setting.MinODjog + 1) + new_N_OD; // P->N order
                
                // ****************** how to save? **********************

                if (minOffset[key] == MAX_OFFSET) {
                    minOffset[key] = currOffset;
                    imsiPrevBestStates[key].clear();
                    imsiPrevBestStates[key].push_back(prevDstate.index);
                }
                else {
                    if (currOffset < minOffset[key]) {
                        minOffset[key] = currOffset;
                        imsiPrevBestStates[key].clear();
                        imsiPrevBestStates[key].push_back(prevDstate.index);
                    }
                    else if (currOffset == minOffset[key]) {
                        imsiPrevBestStates[key].push_back(prevDstate.index);
                    }
                }
            }

            for (int p_od = 0; p_od <= setting.MinODjog; p_od++) {
                for (int n_od = 0; n_od <= setting.MinODjog; n_od++) {
                    int index = p_od * (setting.MinODjog + 1) + n_od;
                    if (minOffset[index] == MAX_OFFSET) {
                        assert(imsiPrevBestStates[index].empty());
                        continue;
                    }
                    int _rightNoffset = minOffset[index] + currState.getSize() - currState.rightNzero - 1;
                    int _rightPoffset = minOffset[index] + currState.getSize() - currState.rightPzero - 1;
                    std::string _rightNnet = currState.getNRightNet();
                    std::string _rightPnet = currState.getPRightNet();
                    int _rightNfin = currState.getNLastFin();
                    int _rightPfin = currState.getPLastFin();
                    std::vector<int> _prevBestStates = imsiPrevBestStates[index];

                    assert(_rightNoffset >= 0);
                    assert(_rightPoffset >= 0);
                    assert(_rightNfin >= 0);
                    assert(_rightPfin >= 0);

                    curr.dstates.emplace_back(dindex++, currState.index, minOffset[index], _rightNoffset, _rightPoffset, _rightNfin, _rightPfin, n_od, p_od, _rightNnet, _rightPnet, _prevBestStates, false, true);

                        
                }
            }
        }
    }
    else if (curr.type == unitType::PONLY) {        

        for (auto& currState : curr.states) {

            for (auto& prevDstate : prev.dstates) {
                if (!prevDstate.enable) continue;

                // Calculate P offset
                int PBaseOffset = prevDstate.rightPoffset + 1 - currState.leftPzero;

                // Net difference
                int NetGap;
                if (!prevDstate.rightPnet.empty() && prevDstate.rightPnet != currState.getPLeftNet()) NetGap = setting.NetDiffGap;
                else NetGap = 0;

                // Fin difference
                int FinGap;
                assert(currState.PfirstFin > 0);
                assert(currState.PfirstFinHeight > 0);
                if (prevDstate.rightPfin > 0 && prevDstate.rightPfin != currState.getPFirstFin()) FinGap = setting.WidthDiffGap;
                else FinGap = 0;

                // Min OD difference
                int ODGap;
                if (currState.PsecondFin > 0 && currState.PfirstFin < currState.PsecondFin) { // case 1
                    if (prevDstate.rightPfin < currState.PfirstFin) {        // Case 1-1
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else if (prevDstate.rightPfin == currState.PfirstFin) { // Case 1-2
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD - currState.PfirstFinHeight - currState.centerPzero > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD - currState.PfirstFinHeight - currState.centerPzero) : 0; 
                    }
                    else {   // Case 1-3
                        ODGap = (setting.MinODjog + 1 - currState.PfirstFinHeight - currState.centerPzero > 0) ? (setting.MinODjog + 1 - currState.PfirstFinHeight - currState.centerPzero) : 0;
                    }
                }
                else if (currState.PsecondFin > 0 && currState.PfirstFin > currState.PsecondFin) {
                    if (currState.PfirstFin > prevDstate.rightPfin) {       // Case 2-1
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else ODGap = 0;     // Case 2-2
                }
                else if (currState.PfirstFin > 0) {   // Case 3 (one kind of fins)
                    assert(currState.PsecondFin == 0);
                    if (currState.PfirstFin > prevDstate.rightPfin) {
                        if (prevDstate.P_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.P_OD > 0) ? (setting.MinODjog + 1 - prevDstate.P_OD) : 0;
                    }
                    else {
                        ODGap = 0;
                    }
                }
                int DiffGap = std::max(std::max(NetGap, FinGap), ODGap);

                int Poffset = PBaseOffset + DiffGap;

                // Calculate New_P_OD
                int new_P_OD;

                int p_gap = Poffset + currState.leftPzero - prevDstate.rightPoffset - 1;
                if (currState.PsecondFin > 0 && currState.PfirstFin < currState.PsecondFin) new_P_OD = 0;
                else if (currState.PsecondFin > 0 && currState.PfirstFin > currState.PsecondFin) {
                    new_P_OD = (currState.centerPzero + currState.PsecondFinHeight > setting.MinODjog) ? 0 : (currState.centerPzero + currState.PsecondFinHeight);
                }
                else {
                    if (prevDstate.rightPfin < currState.PfirstFin) new_P_OD = 0;
                    else if (prevDstate.rightPfin == currState.PfirstFin) {
                        if (prevDstate.P_OD == 0) new_P_OD = 0;
                        else new_P_OD = (prevDstate.P_OD + p_gap + currState.PfirstFinHeight > setting.MinODjog) ? 0 : (prevDstate.P_OD + p_gap + currState.PfirstFinHeight);
                    }
                    else new_P_OD = (p_gap + currState.PfirstFinHeight > setting.MinODjog) ? 0 : (p_gap + currState.PfirstFinHeight);
                }

                int _rightNoffset = prevDstate.rightNoffset;
                int _rightPoffset = Poffset + currState.getSize() - currState.rightPzero - 1;
                std::string _rightNnet = prevDstate.rightNnet;
                std::string _rightPnet = currState.getPRightNet();
                int _rightNfin = prevDstate.rightNfin;
                int _rightPfin = currState.getPLastFin();
                std::vector<int> _prevBestStates;
                _prevBestStates.push_back(prevDstate.index);
                int n_od = prevDstate.N_OD;
                int p_od = new_P_OD;

                curr.dstates.emplace_back(dindex++, currState.index, Poffset, _rightNoffset, _rightPoffset, _rightNfin, _rightPfin, n_od, p_od, _rightNnet, _rightPnet, _prevBestStates, false, true);

            }
        }
    }

    else if (curr.type == unitType::NONLY) {

        for (auto& currState : curr.states) {

            for (auto& prevDstate : prev.dstates) {
                if (!prevDstate.enable) continue;

                // Calculate N offset
                int Noffset;
                int NBaseOffset = prevDstate.rightNoffset + 1 - currState.leftNzero;

                // Net difference
                int NetGap;
                if (!prevDstate.rightNnet.empty() && prevDstate.rightNnet != currState.getNLeftNet()) NetGap = setting.NetDiffGap;
                else NetGap = 0;

                // Fin difference
                int FinGap;
                assert(currState.NfirstFin > 0);
                assert(currState.NfirstFinHeight > 0);
                if (prevDstate.rightNfin > 0 && prevDstate.rightNfin != currState.getNFirstFin()) FinGap = setting.WidthDiffGap;
                else FinGap = 0;

                // Min OD difference
                int ODGap;
                if (currState.NsecondFin > 0 && currState.NfirstFin < currState.NsecondFin) { // case 1
                    if (prevDstate.rightNfin < currState.NfirstFin) {        // Case 1-1
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else if (prevDstate.rightNfin == currState.NfirstFin) { // Case 1-2
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD - currState.NfirstFinHeight - currState.centerNzero > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD - currState.NfirstFinHeight - currState.centerNzero) : 0; 
                    }
                    else {   // Case 1-3
                        ODGap = (setting.MinODjog + 1 - currState.NfirstFinHeight - currState.centerNzero > 0) ? (setting.MinODjog + 1 - currState.NfirstFinHeight - currState.centerNzero) : 0;
                    }
                }
                else if (currState.NsecondFin > 0 && currState.NfirstFin > currState.NsecondFin) {
                    if (currState.NfirstFin > prevDstate.rightNfin) {       // Case 2-1
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else ODGap = 0;     // Case 2-2
                }
                else if (currState.NfirstFin > 0) {   // Case 3 (one kind of fins)
                    assert(currState.NsecondFin == 0);
                    if (currState.NfirstFin > prevDstate.rightNfin) {
                        if (prevDstate.N_OD == 0) ODGap = 0;
                        else ODGap = (setting.MinODjog + 1 - prevDstate.N_OD > 0) ? (setting.MinODjog + 1 - prevDstate.N_OD) : 0;
                    }
                    else {
                        ODGap = 0;
                    }
                }
                int DiffGap = std::max(std::max(NetGap, FinGap), ODGap);

                Noffset = NBaseOffset + DiffGap;

                // calculate new_N_OD
                int new_N_OD;
                int n_gap = Noffset + currState.leftNzero - prevDstate.rightNoffset - 1;
                if (currState.NsecondFin > 0 && currState.NfirstFin < currState.NsecondFin) new_N_OD = 0;
                else if (currState.NsecondFin > 0 && currState.NfirstFin > currState.NsecondFin) {
                    new_N_OD = (currState.centerNzero + currState.NsecondFinHeight > setting.MinODjog) ? 0 : (currState.centerNzero + currState.NsecondFinHeight);
                }
                else {
                    if (prevDstate.rightNfin < currState.NfirstFin) new_N_OD = 0;
                    else if (prevDstate.rightNfin == currState.NfirstFin) {
                        if (prevDstate.N_OD == 0) new_N_OD = 0;
                        else new_N_OD = (prevDstate.N_OD + n_gap + currState.NfirstFinHeight > setting.MinODjog) ? 0 : (prevDstate.N_OD + n_gap + currState.NfirstFinHeight);
                    }
                    else new_N_OD = (n_gap + currState.NfirstFinHeight > setting.MinODjog) ? 0 : (n_gap + currState.NfirstFinHeight);
                }

                int _rightNoffset = Noffset + currState.getSize() - currState.rightNzero - 1;
                int _rightPoffset = prevDstate.rightPoffset;
                std::string _rightNnet = currState.getNRightNet();
                std::string _rightPnet = prevDstate.rightPnet;
                int _rightNfin = currState.getNLastFin();
                int _rightPfin = prevDstate.rightPfin;
                std::vector<int> _prevBestStates;
                _prevBestStates.push_back(prevDstate.index);
                int n_od = new_N_OD;
                int p_od = prevDstate.P_OD;

                curr.dstates.emplace_back(dindex++, currState.index, Noffset, _rightNoffset, _rightPoffset, _rightNfin, _rightPfin, n_od, p_od, _rightNnet, _rightPnet, _prevBestStates, false, true);
            }
        }
    }

    if (setting.remove_dom) curr.disableRedundantDStates();

}
