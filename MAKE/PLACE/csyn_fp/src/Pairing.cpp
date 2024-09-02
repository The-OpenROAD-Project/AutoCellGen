////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2024, The Regents of the University of California
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

#include "../header/Pairing.h"
#include <map>
#include <set>
#include <list>
#include <string>

void Pairer::pairing() {
    num_tran = static_cast<int>(cell.trans.size());

    ispaired.resize(num_tran, false);

    grouping();

	find_complement_net();

    if (comp_net_list.size() > 0) find_transmission_candidate();

    if (transmission_list.size() > 0) pairing_cross_coupled();
    
    pairing_transistors();

    std::cout << "Pairing done!" << std::endl;

}

void Pairer::grouping() {

	std::cout << cell.name << std::endl;

	std::list<std::string> logical_partition_list{ "DFFHQN", "DFFLQN", "SDFH", "SDFL", "ASYNC_DFFH" };

	std::string tr_array[5][5][20]=
	{
		{
			{"MM3", "MM5"},
			{"MM1", "MM4", "MM11", "MM10", "MM7", "MM9", "MM8", "MM6"},
			//{"MM13", "MM12"},
			{"MM13", "MM12", "MM19", "MM18", "MM15", "MM17", "MM16", "MM14"},
			{"MM20", "MM23", "MM21", "MM22"},
			{"MM25", "MM24"}
		},

		{
			{"MM3", "MM5"},
			{"MM1", "MM4", "MM11", "MM10", "MM7", "MM9", "MM8", "MM6"},
			//{"MM13", "MM12"},
			{"MM13", "MM12", "MM19", "MM18", "MM15", "MM17", "MM16", "MM14"},
			{"MM20", "MM23", "MM21", "MM22"},
			{"MM25", "MM24"}
		},

		{
			{"MM26", "MM2", "MM3", "MM27", "MM31", "MM30", "MM29", "MM28", "MM5", "MM0"},
			{"MM1", "MM4", "MM11", "MM10", "MM7", "MM9", "MM8", "MM6"},
			//{"MM13", "MM12"},
			{"MM13", "MM12", "MM19", "MM18", "MM15", "MM17", "MM16", "MM14"},
			{"MM21", "MM22", "MM20", "MM23"},
			{"MM25", "MM24"}
		},

		{
			{"MM30", "MM27", "MM31", "MM3", "MM2", "MM0", "MM32", "MM26", "MM29", "MM5"},
			{"MM1", "MM4", "MM11", "MM10", "MM7", "MM9", "MM8", "MM6"},
			//{"MM13", "MM12"},
			{"MM13", "MM12", "MM15", "MM18", "MM19", "MM17", "MM14", "MM16"},
			{"MM21", "MM22", "MM20", "MM23"},
			{"MM25", "MM24"}
		},


		{
			{"MM3", "MM5"},
			{"MM1", "MM4", "MM49", "MM11", "MM10", "MM46", "MM7", "MM9", "MM8", "MM48", "MM6", "MM43"},
			//{"MM13", "MM12"},
			{"MM13", "MM12", "MM42", "MM37", "MM35", "MM45", "MM28", "MM34", "MM47", "MM33", "MM29", "MM44"},
			{"MM21", "MM22", "MM20", "MM23"},
			{"MM25", "MM24"}
		}
	};


	std::vector<int> group_vec[5];

	bool is_in_logical_partition_list = false;

	if(setting.logical_partition == true){
		int cnt = 0;
		for (auto it : logical_partition_list){
			if(cell.name.substr(0, it.length()) == it){
				int index = 0;
				for (const auto& tran : cell.trans) {
					for(int i=0; i<5; i++){
						for(int j=0; j<20; j++){
							if(tran.name == tr_array[cnt][i][j]){
								group_vec[i].push_back(index);
							}
						}
					}
					index++;
				}
				is_in_logical_partition_list = true;
			}
			cnt++;
		}

		for(auto & it : group_vec){
			for(auto & itt : it){
				std::cout << cell.trans[itt].name << " ";
			}
			std::cout << std::endl;
			groups.push_back(it);
		}
	}

	else{

		std::cout << cell.name << std::endl;
		int numNet = cell.nets.size();

		std::vector<bool> pnets(numNet, false);
		std::vector<bool> nnets(numNet, false);

		// find nets connected both PMOS and NMOS
		auto checkNet = [&](std::string netName, transtype type) {
			for (int i = 0; i < numNet; i++) {
				if (netName == cell.nets[i]) {
					if (type == transtype::NMOS) nnets[i] = true;
					else pnets[i] = true;
				}
			}
		};

		// check transistor's connected nets
		for (const auto& tran : cell.trans) {
			checkNet(tran.drain, tran.type);
			checkNet(tran.source, tran.type);
		}
		
		// find center net
		std::vector<std::string> centerNets;
		for (int i = 0; i < numNet; i++) {
			if (pnets[i] && nnets[i]) centerNets.push_back(cell.nets[i]);
		}

		/* Group transistors connected to same center net */

		int numTrans = cell.trans.size();
		std::vector<bool> visited(numTrans, false);
		
		// check if two transistors are connected (except through VDD or VSS)  
		auto transConnected = [&](Transistor &a, Transistor &b) {
			std::vector<std::string> tempa;
			if (a.drain != "VDD" && a.drain != "VSS") tempa.push_back(a.drain);
			if (a.source != "VDD" && a.source != "VSS") tempa.push_back(a.source);
			
			std::vector<std::string> tempb;
			if (b.drain != "VDD" && b.drain != "VSS") tempb.push_back(b.drain);
			if (b.source != "VDD" && b.source != "VSS") tempb.push_back(b.source);

			for (auto neta : tempa) {
				for (auto netb : tempb) {
					if (neta == netb) return true;
				}
			}
			return false;
		};

		for (auto centerNet : centerNets) {
			std::queue<int> q;
			// collect transistors that one of S/D is centerNet
			for (int i = 0; i < cell.trans.size(); i++) {
				Transistor &tran = cell.trans[i];
				if (tran.source == centerNet || tran.drain == centerNet) {
					if (!visited[i]) {
						q.push(i);
						visited[i] = true;
					}
				}
			}

			std::vector<int> group;

			// search transistors connected to centerNet
			while (!q.empty()) {
				int index = q.front();
				Transistor &tran = cell.trans[index];
				group.push_back(index);
				q.pop();

				for (int i = 0; i < cell.trans.size(); i++) {
					Transistor &temp = cell.trans[i];
					if (!visited[i] && transConnected(tran, temp)) {
						q.push(i);
						visited[i] = true;        
					}
				}
			}

			if (group.size() > 0) groups.push_back(group);
		}

		for (int i = 0; i < cell.trans.size(); i++) {
			if (!visited[i]) {
				std::cout << "Unvisited transistors exist!" << std::endl;
				std::vector<int> group;
				group.push_back(i);
				groups.push_back(group);
			}
		}
		
	}

	
	// connect partitions
	
	if (setting.merge_group){
		int step = 0;
		while(true){
			bool is_end = true;

			std::map<int, std::map<std::string, int> > group_net;
			std::vector<int> intra_net_num;

			std::cout << step++ << std::endl;

			if(groups.size() == 1) break;

			for (int i = 0; i < groups.size(); i++){
				std::cout << "each groups' size : " << groups[i].size() << std::endl;
				auto& group_index = groups[i];
				int num_tran_group = static_cast<int>(group_index.size());

				if(num_tran_group < setting.MinTrNum){
					std::cout << num_tran_group << std::endl;
					std::cout << setting.MinTrNum << std::endl;
					is_end = false;
				}

				std::map<std::string, int> net_name_map;

				for (int j=0; j < num_tran_group; j++){
					std::cout << cell.trans[group_index[j]] << std::endl;
					std::cout << cell.trans[group_index[j]].source << cell.trans[group_index[j]].gate << cell.trans[group_index[j]].drain << std::endl;

					std::string source_net = cell.trans[group_index[j]].source;
					std::string gate_net = cell.trans[group_index[j]].gate;
					std::string drain_net = cell.trans[group_index[j]].drain;

					if (net_name_map.find(source_net) != net_name_map.end()) net_name_map.find(source_net)->second += 1;
					else net_name_map.insert(std::pair<std::string, int>(source_net, 1));
			
					if (net_name_map.find(gate_net) != net_name_map.end()) net_name_map.find(gate_net)->second += 1;
					else net_name_map.insert(std::pair<std::string, int>(gate_net, 1));

					if (net_name_map.find(drain_net) != net_name_map.end()) net_name_map.find(drain_net)->second += 1;
					else net_name_map.insert(std::pair<std::string, int>(drain_net, 1));
				}

				intra_net_num.push_back(net_name_map.size()-2);

				group_net.insert(std::pair<int, std::map<std::string, int> >(i, net_name_map));
			}

			// if all group tr size > Min transistor size, then end the loop
			if(is_end) break;

			for(auto & it : group_net){
				std::cout << "idx : " << it.first << std::endl;

				for(auto & itt : it.second){
					std::cout << itt.first <<  " : " << itt.second  << std::endl;
				}
				std::cout << std::endl;
			}

			num_group = static_cast<int>(groups.size());

			int **edge = (int**)malloc(sizeof(int*) * num_group);
			for(int i=0; i<num_group; i++){
				edge[i] = (int*)malloc(sizeof(int) * num_group);
			}

			for(int i=0; i<num_group; i++){
				for(int j=0; j<num_group; j++){
					edge[i][j] = 0;
					if(i == j) continue;

					for(auto & it : group_net.find(i)->second){
						if(it.first == "VSS" || it.first == "VDD") continue;

						if(group_net.find(j)->second.find(it.first) != group_net.find(j)->second.end()){
							edge[i][j] += 1;
						}
					}
				}
			}

			int groupA;
			int groupB;
			int max_inter = 0;
			int min_intra = 10000;
			bool using_max_intra = true;
		
			for(int i=0; i<num_group; i++){
				if(!using_max_intra && intra_net_num[i] > setting.MaxIntraNetNum) continue;
				for(int j=0; j<num_group; j++){
					if(!using_max_intra && intra_net_num[j] > setting.MaxIntraNetNum) continue;
					if(i == j) continue;

					if(edge[i][j] > max_inter){
						max_inter = edge[i][j];
						min_intra = intra_net_num[i]+intra_net_num[j];
						groupA = i;
						groupB = j;

						if(intra_net_num[i] < setting.MaxIntraNetNum && intra_net_num[j] < setting.MaxIntraNetNum) using_max_intra = false;
					}

					else if(edge[i][j] == max_inter){
						if(intra_net_num[i]+intra_net_num[j] < min_intra){
							min_intra = intra_net_num[i]+intra_net_num[j];
							groupA = i;
							groupB = j;

							if(intra_net_num[i] < setting.MaxIntraNetNum && intra_net_num[j] < setting.MaxIntraNetNum) using_max_intra = false;
						}
					}
				}
			}

			std::cout << "A : " << groupA << ", B : " << groupB << std::endl;

			int temp;
			if(groupA > groupB){
				temp = groupA;
				groupA = groupB;
				groupB = temp;
			}

			std::vector<int> group_new;

			for(auto& it: groups[groupA]) group_new.push_back(it);
			for(auto& it: groups[groupB]) group_new.push_back(it);
			
			groups.erase(groups.begin() + groupB);
			groups.erase(groups.begin() + groupA);

			groups.push_back(group_new);
		}
	}

    num_group = static_cast<int>(groups.size());
}


void Pairer::find_complement_net() {
    for (int g = 0; g < num_group; g++) {
        auto& group_index = groups[g];
        int num_tran_group = static_cast<int>(group_index.size());

        for (int i = 0; i < num_tran_group; i++) {
            if (ispaired[group_index[i]]) continue;
            if (cell.trans[group_index[i]].type != transtype::NMOS) continue;
            auto& curr_nmos = cell.trans[group_index[i]];
            if (curr_nmos.source != "VSS" && curr_nmos.drain != "VSS") continue;
            std::string nmos_other_net = (curr_nmos.source == "VSS") ? (curr_nmos.drain) : (curr_nmos.source);

            for (int j = 0; j < num_tran_group; j++) {
                if (ispaired[group_index[j]]) continue;
                if (cell.trans[group_index[j]].type != transtype::PMOS) continue;
                auto& curr_pmos = cell.trans[group_index[j]];
                if (curr_pmos.source != "VDD" && curr_pmos.drain != "VDD") continue;
                std::string pmos_other_net = (curr_pmos.source == "VDD") ? (curr_pmos.drain) : (curr_pmos.source);

                // inverter found
                if (nmos_other_net == pmos_other_net && curr_nmos.gate == curr_pmos.gate) {
                    comp_net_list.emplace_back(nmos_other_net, curr_nmos.gate);
                    comp_net_list.emplace_back(curr_nmos.gate, nmos_other_net);

                    Pair p;
                    p.pmos.push_back(curr_pmos);
                    p.nmos.push_back(curr_nmos);

                    pair_list.push_back(std::move(p));
                    pairGroup[static_cast<int>(pair_list.size()) - 1] = g;
                    
                    ispaired[group_index[i]] = true;
                    ispaired[group_index[j]] = true;
                    
                }
            }
        }
    }
}
// find transistor pairs whose gates are complement net and sharing nets in S/D region
void Pairer::find_transmission_candidate() {
    for (int g = 0; g < num_group; g++) {
        auto& group_index = groups[g];
        int num_tran_group = static_cast<int>(group_index.size());

        for (int i = 0; i < num_tran_group; i++) {
            if (ispaired[group_index[i]]) continue;
            if (cell.trans[group_index[i]].type != transtype::NMOS) continue;
            auto& curr_nmos = cell.trans[group_index[i]];

            for (int j = 0; j < num_tran_group; j++) {
                if (ispaired[group_index[j]]) continue;
                if (cell.trans[group_index[j]].type != transtype::PMOS) continue;
                auto& curr_pmos = cell.trans[group_index[j]];

                if (curr_nmos.source == curr_pmos.source || curr_nmos.drain == curr_pmos.source || curr_nmos.source == curr_pmos.drain || curr_nmos.drain == curr_pmos.drain) {
                    
                    bool isExist = false;
                    for (auto& comp_net_pair : comp_net_list) {
                        if (comp_net_pair.first == curr_nmos.gate && comp_net_pair.second == curr_pmos.gate) {
                            isExist = true;
                            break;
                        }
                    }
                    
                    if (isExist) {
                        transmission_list.emplace_back(group_index[j], group_index[i], g);
                    }
                }
            }
        }
    }
}

void Pairer::pairing_cross_coupled() {
    int num_trans_cand = static_cast<int>(transmission_list.size());

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
 

    for (int i = 0; i < num_trans_cand - 1; i++) {
        for (int j = i + 1; j < num_trans_cand; j++) {

            int pmos1_index = std::get<0>(transmission_list[i]);
            int nmos1_index = std::get<1>(transmission_list[i]);
            int pmos2_index = std::get<0>(transmission_list[j]);
            int nmos2_index = std::get<1>(transmission_list[j]);

            if (std::get<2>(transmission_list[i]) != std::get<2>(transmission_list[j])) continue;

            if (ispaired[pmos1_index]) continue;
            if (ispaired[nmos1_index]) continue;
            if (ispaired[pmos2_index]) continue;
            if (ispaired[nmos2_index]) continue;

            auto& pmos1 = cell.trans[pmos1_index];
            auto& nmos1 = cell.trans[nmos1_index];
            auto& pmos2 = cell.trans[pmos2_index];
            auto& nmos2 = cell.trans[nmos2_index];

            auto common1 = find_common_net(pmos1.source, pmos1.drain, nmos1.source, nmos1.drain);
            auto common2 = find_common_net(pmos2.source, pmos2.drain, nmos2.source, nmos2.drain);

            for (auto common_net1 : common1) {
                for (auto common_net2 : common2) {
                    if (common_net1 == common_net2) {
                        Pair p;
                        p.is_xc_pair = true;
                        p.pmos.push_back(cell.trans[pmos1_index]);
                        p.nmos.push_back(cell.trans[nmos1_index]);
                        p.pmos.push_back(cell.trans[pmos2_index]);
                        p.nmos.push_back(cell.trans[nmos2_index]);

                        pair_list.push_back(std::move(p));

                        pairGroup[static_cast<int>(pair_list.size()) - 1] = std::get<2>(transmission_list[i]);
                        
                        ispaired[pmos1_index] = true;
                        ispaired[nmos1_index] = true;
                        ispaired[pmos2_index] = true;
                        ispaired[nmos2_index] = true;
                    
                        break;
                    }
                }
            }
       
        }
    }
}

void Pairer::pairing_transistors() {
    for (int g = 0; g < num_group; g++) {
        auto& group_index = groups[g];
        int num_tran_group = static_cast<int>(group_index.size());

        if (num_tran_group == 0) continue;

        for (int i = 0; i < num_tran_group; i++) {
            if (cell.trans[group_index[i]].type != transtype::NMOS) continue;
            for (int j = 0; j < num_tran_group; j++) {
                if (cell.trans[group_index[j]].type != transtype::PMOS) continue;
                assert(i != j);
                assert(cell.trans[group_index[i]].type != cell.trans[group_index[j]].type);
                if (!ispaired[group_index[i]] && !ispaired[group_index[j]] && cell.trans[group_index[i]].gate == cell.trans[group_index[j]].gate) {
                    Pair p;
                    p.pmos.push_back(cell.trans[group_index[j]]);
                    p.nmos.push_back(cell.trans[group_index[i]]);
                    pair_list.push_back(std::move(p));
                    pairGroup[static_cast<int>(pair_list.size()) - 1] = g;
                    ispaired[group_index[i]] = true;
                    ispaired[group_index[j]] = true;
                }
            
            }
        }
        for (int i = 0; i < num_tran_group; i++) {
            if (!ispaired[group_index[i]]) {
                Pair p;
                if (cell.trans[group_index[i]].type == transtype::NMOS) {
                    p.nmos.push_back(cell.trans[group_index[i]]);
                }
                else if (cell.trans[group_index[i]].type == transtype::PMOS) {
                    p.pmos.push_back(cell.trans[group_index[i]]);
                }
                else { std::cout << "Error!" << std::endl; }
                pair_list.push_back(std::move(p));
                pairGroup[static_cast<int>(pair_list.size()) - 1] = g;
            }
        }
    }
}
