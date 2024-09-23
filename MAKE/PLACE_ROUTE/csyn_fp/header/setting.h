#pragma once

#include <string>

class Setting {
public:
    std::string tech; 

    int WidthDiffGap;
    int NetDiffGap;
    int NMOSMaxAllowedFin;
    int PMOSMaxAllowedFin;
    int MinODjog;
    int MaxStep;

	int MinTrNum;
	int MaxIntraNetNum;
	
	bool merge_group;
	bool logical_partition;

    int numSolutions;
	int routeSolutions;

    int XC;

    int relaxation;

    int route_accept;

    std::string folding_style;

    bool remove_sym, remove_dom, branch_bound, refine_sol;
    bool avoid_gatecut;

    bool min_m2, min_m1, gen_gds;



    std::string m1_dir, m2_dir;

//    bool sideJogAllow = true;

};

extern Setting setting;
