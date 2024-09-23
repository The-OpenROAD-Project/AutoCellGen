#include "../header/GroupPlacer.h"

void GroupPlacer::run() {

    Pairer pairer(cell);
    pairer.pairing();

    // need to modify (copy to reference)
    pairGroup = pairer.pairGroup;
    pairs = pairer.pair_list;


    for (int i = 0; i < pairs.size(); i++) {
        std::cout << "Pair " << i << " (group " << pairGroup[i] << ") : ";
        if (pairs[i].nmos.size() > 0) std::cout << pairs[i].nmos[0].name << " ";
        if (pairs[i].pmos.size() > 0) std::cout << pairs[i].pmos[0].name;
        std::cout << std::endl;
    
    }
    // 1. generate placer per each group
    numGroup = pairer.num_group;
    std::vector<Placer> placers(numGroup);
    for (auto& placer : placers) placer.min_width = MAX_OFFSET;
    for (int i = 0; i < pairs.size(); i++) {
        int group = pairGroup[i];
        placers[group].pairs.push_back(pairs[i]);
    }

    // 2. get solution of each placer
    int group_index = 0;
    std::vector<int> num_sol;
    for (auto& placer : placers) {
        std::cout << "Group " << group_index++ << std::endl;
        placer.runEachGroup();

        std::vector<PlaceGrid> solution_all;
        for (auto& solution_pair : placer.solutions) {
            if (solution_pair.first > placer.min_width + setting.relaxation) continue;

            auto& solution_set = solution_pair.second;
            for (auto& solution : solution_set) {
                solution_all.push_back(solution);
            }
        }
        num_sol.push_back(solution_all.size());

        //if (placer.numUnit > 1) groupUnits.emplace_back(placer.solutions[placer.min_width], true);
        //else groupUnits.emplace_back(placer.solutions[placer.min_width], false);
        if (placer.numUnit > 1) groupUnits.emplace_back(solution_all, true);
        else groupUnits.emplace_back(solution_all, false);
    
    
    }
    
    for (int i = 0; i < placers.size(); i++) {
        std::cout << "Group " << i << " : min_width = " << placers[i].min_width << ", num Sols = " << num_sol[i] << std::endl;
    }
    int index = 0;
    numGroupUnit = groupUnits.size();

    // 3. Search again with groupUnit
    runSearchwithRelax();

	//std::string filePath = fs::current_path() / fs::path("input/7.5Tdataset/placement/" + cell.name + ".txt");
    std::string filePath = out_dir + "/" + cell.name + ".txt";
    std::cout<<"filePath: "<<filePath<<std::endl;
    printSolution(filePath);

    //fs::path outPath = fs::current_path() / fs::path("placements") / fs::path(cell.name);
    //fs::create_directories(outPath);
    //print_refinedSol(outPath);

}

void GroupPlacer::runSearchwithRelax() {
    numGroupUnit = groupUnits.size();

    std::vector<int> order(numGroup, -1);
    lower_bound = MAX_OFFSET;
    findGroupSolution(0, -1, order, false);
    min_width = lower_bound;

    if (setting.relaxation > 0) {
        lower_bound = min_width + setting.relaxation;
        findGroupSolution(0, -1, order, true);
    }
}


void GroupPlacer::printSolution(std::string outPath) {

    for (int width = min_width; width <= min_width + setting.relaxation; width++) {
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
            }            
        }
        out.close();
    }

}

void GroupPlacer::findGroupSolution(int curr, int prev, std::vector<int>& order, bool fix_bound) {

    // removing symetric solution
    
    if (setting.remove_sym) {

        if (curr >= (numGroupUnit + 1) / 2) {
            if (numGroupUnit % 2 == 0) {
                if (order[0] < 0) return;
            }
            else {
                if (order[0] < 0) return;
                if (order[0] == (numGroupUnit + 1) / 2 && order[1] < 0) return;
            }
        }
    }

    // branch and bound
    /*
    if (min_width < MAX_OFFSET && prev != -1) {
        
        int nMinRemain = 0;
        int pMinRemain = 0;
        for (int i = 0; i < numGroupUnit; i++) {
            if (order[i] < 0) {
                nMinRemain += groupUnits[i].nMinLeg;
                pMinRemain += groupUnits[i].pMinLeg;
            }
        }

        int count = 0;
        for (auto& dstate : units[prev].dstates) {
            if (!dstate.enable) continue;
            count++;
            int nLowerBound = nMinRemain + dstate.rightNoffset;
            int pLowerBound = pMinRemain + dstate.rightPoffset;
            if (std::max(pLowerBound, nLowerBound) > min_width) {
                dstate.enable = false;
                count--;
            }
        }
        if (count == 0) {
            //std::cout << "min_width : " << min_width << std::endl;
            //std::cout << "nMinRemain : " << nMinRemain << ", pMinRemain : " << pMinRemain << std::endl;
            return;
        }
        
    }
*/
    // reach the leaf node, find solution
    if (curr >= numGroupUnit) {
        for (int i = 0; i < numGroupUnit; i++) {
            if (order[i] < 0) {
                std::cout << "Error : Unexplored Group units!" << std::endl;
                return;
            }
        }

        for (const auto& dstate : groupUnits[prev].dstates) {

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

            //if (solutions[lower_bound].size() >= setting.numSolutions) continue;

            //std::cout << "Start backtracking solution" << std::endl;

            numGroupUnit = groupUnits.size();
            std::vector<int> sol(numGroupUnit, -1);
            sol[numGroupUnit - 1] = dstate.index;
            
            backtrackGroupSolution(dstate.index, sol, order, numGroupUnit - 1, dstateWidth);

        
        }
        return;
    }

    for (int i = 0; i < numGroupUnit; i++) {
        if (order[i] < 0) {
            if (curr == 0) {
                order[i] = 0;

                groupUnits[i].initiateFirstGroupUnit();       // generate first unit of dstates
                //units[i].disableRedundantDStates(); // disable redundant dstates
            
                findGroupSolution(curr + 1, i, order, fix_bound);
                
                order[i] = -1;
                groupUnits[i].resetGroupDstates(); // MAX_OFFSET
            }
            else {
                order[i] = curr;
                calculateGroupState(groupUnits[prev], groupUnits[i]);

                findGroupSolution(curr + 1, i, order, fix_bound);

                groupUnits[i].resetGroupDstates();
                order[i] = -1;
            }
        }
    }
}

void GroupPlacer::backtrackGroupSolution(int currIndex, std::vector<int> &dstateList, std::vector<int> &order, int currOrder, int width)  {
    dstateList[currOrder] = currIndex;

    auto findUnitIndex = [&](int unit_order) {
        for (int i = 0; i < numGroupUnit; i++) 
            if (order[i] == unit_order)
                return i;
        std::cout << "Can't find unit!" << std::endl;
        return -1;
    };

    if (currOrder == 0) {
        OutputTrans dummy("dummy", "dummy", "dummy", "dummy", 0);
        std::vector<OutputTrans> nSol(width, dummy);
        std::vector<OutputTrans> pSol(width, dummy);

        for (int i = 0; i < dstateList.size(); i++) {
            assert(i < order.size());
            //std::cout << i << std::endl;            
            assert(findUnitIndex(i) < groupUnits.size());
            const PlaceGroupUnit &unit = groupUnits[findUnitIndex(i)];

            assert(dstateList[i] < unit.dstates.size());
            const DynamicGroupState &dstate = unit.dstates[dstateList[i]];

            assert(dstate.hostIndex < unit.states.size());
            const GroupUnitState &state = unit.states[dstate.hostIndex];

            for (int x = 0; x < state.width; x++) {
               assert(dstate.offset + x < nSol.size());
               nSol[dstate.offset + x] = state.placement.nmos[x];

               assert(dstate.offset + x < pSol.size());
               pSol[dstate.offset + x] = state.placement.pmos[x];
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
    for (auto prevDstateIndex : groupUnits[unitIndex].dstates[currIndex].prevBestStates) {
        backtrackGroupSolution(prevDstateIndex, dstateList, order, currOrder - 1, width);
    }


    dstateList[currOrder] = -1;
}

void GroupPlacer::calculateGroupState(PlaceGroupUnit& prev, PlaceGroupUnit& curr) {
    int dindex = 0;
    for (auto& currState : curr.states) {
        // store best states
        int minOffset = MAX_OFFSET;
        std::vector<int> imsiPrevBestStates;
        for (const auto& prevDstate : prev.dstates) {

            if (!prevDstate.enable) continue;

            int pOffset = prevDstate.rightPoffset + 1 - currState.leftPdummy;
            int P_DiffGap = 0;

            if (!prevDstate.rightPnet.empty() && prevDstate.rightPnet != currState.leftPnet)
                P_DiffGap = std::max(setting.NetDiffGap, P_DiffGap);
            assert(prevDstate.rightPfin > 0);
            if (prevDstate.rightPfin > 0 && prevDstate.rightPfin != currState.getPFirstFin())
                P_DiffGap = std::max(setting.WidthDiffGap, P_DiffGap);
            pOffset += P_DiffGap;
            if (pOffset <= 0) pOffset = 0;

            int nOffset = prevDstate.rightNoffset + 1 - currState.leftNdummy;
            int N_DiffGap = 0;
            if (!prevDstate.rightNnet.empty() && prevDstate.rightNnet != currState.leftNnet)
                N_DiffGap = std::max(setting.NetDiffGap, N_DiffGap);
            assert(prevDstate.rightNfin > 0);
            if (prevDstate.rightNfin > 0 && prevDstate.rightNfin != currState.getNFirstFin())
                N_DiffGap = std::max(setting.WidthDiffGap, N_DiffGap);
                
            nOffset += N_DiffGap;
            if (nOffset <= 0) nOffset = 0;

            int currOffset = std::max(pOffset, nOffset);

            if (currOffset < minOffset) {
                minOffset = currOffset;
                imsiPrevBestStates.clear();
                imsiPrevBestStates.push_back(prevDstate.index);                     
            }
            else if (currOffset == minOffset) {
                imsiPrevBestStates.push_back(prevDstate.index);
            }
        }

        if (imsiPrevBestStates.size() > 0) {
            DynamicGroupState temp(dindex++, currState.index, minOffset, false);
            temp.rightNoffset = temp.offset + currState.width - currState.rightNdummy - 1;
            temp.rightPoffset = temp.offset + currState.width - currState.rightPdummy - 1;
            temp.rightNnet = currState.rightNnet;
            temp.rightPnet = currState.rightPnet;
            temp.rightNfin = currState.getNLastFin();
            temp.rightPfin = currState.getPLastFin();
            temp.enable = true;
            temp.prevBestStates = std::move(imsiPrevBestStates);
            curr.dstates.push_back(std::move(temp));
        }
    }

    if (setting.remove_dom) curr.disableRedundantDStates();

}
void GroupPlacer::print_refinedSol(fs::path outPath) {

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
