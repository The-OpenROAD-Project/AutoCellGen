#include "../header/global.h"
#include "../header/cdlParser.h"
#include "../header/Placer.h"
#include "../header/GroupPlacer.h"
#include "../header/Pairing.h"
#include "../header/Router.h"
#include "../header/ArgumentParser.h"
#include <chrono>
#include <queue>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

void parsing_DR(fs::path& dr_path) {
    //fs::path dr_path = fs::current_path() / fs::path("inputs") / fs::path("dr") / fs::path("ASAP7_placement.dr");
    std::ifstream dr_file(dr_path.string());

    auto split_by_space = [](std::string line) {
	    std::vector<std::string> tokens;
	    size_t prev = line.find_first_not_of(" ");
	    size_t pos;

	    while ((pos = line.find_first_of(" ", prev)) != std::string::npos) {
		    if (pos > prev) tokens.push_back(line.substr(prev, pos - prev));
		    prev = pos + 1;
	    }
	    if (prev < line.length()) tokens.push_back(line.substr(prev, std::string::npos));
	    return tokens;        
    };

    std::string curr_line;
    while (getline(dr_file, curr_line)) {
		std::cout << curr_line << std::endl;
        std::vector<std::string> tokens = split_by_space(curr_line);
        if (tokens.size() < 1) continue;
        if (tokens[0].front() == '#') continue;
        
        if (tokens[0] == "TECH") setting.tech = tokens[1]; 
        else if (tokens[0] == "FIN_DIFF_GAP") setting.WidthDiffGap = std::stoi(tokens[1]);
        else if (tokens[0] == "NET_DIFF_GAP") setting.NetDiffGap = std::stoi(tokens[1]);
        else if (tokens[0] == "NMOS_MAX_FIN") setting.NMOSMaxAllowedFin = std::stoi(tokens[1]);
        else if (tokens[0] == "PMOS_MAX_FIN") setting.PMOSMaxAllowedFin = std::stoi(tokens[1]);
        else if (tokens[0] == "MIN_OD_JOG") setting.MinODjog = std::stoi(tokens[1]);
        else if (tokens[0] == "MAX_STEP") setting.MaxStep = std::stoi(tokens[1]);
        else if (tokens[0] == "MIN_TR_NUM") setting.MinTrNum = std::stoi(tokens[1]);
        else if (tokens[0] == "MAX_INTRA_NUM") setting.MaxIntraNetNum = std::stoi(tokens[1]);
        else if (tokens[0] == "NUM_SOL") setting.numSolutions = std::stoi(tokens[1]);
        else if (tokens[0] == "ROUTE_SOL") setting.routeSolutions = std::stoi(tokens[1]);
        else if (tokens[0] == "XC_NUM") setting.XC = std::stoi(tokens[1]);
        else if (tokens[0] == "RELAXATION") setting.relaxation = std::stoi(tokens[1]);
		else if (tokens[0] == "MERGE_GROUP"){
			if (tokens[1] == "true") setting.merge_group = true;
			else setting.merge_group = false;
		}
		else if (tokens[0] == "LOGICAL_PARTITION"){
			if (tokens[1] == "true") setting.logical_partition = true;
			else setting.logical_partition = false;
		}
        else if (tokens[0] == "AVOID_GATECUT") {
            if (tokens[1] == "true") setting.avoid_gatecut = true;
            else setting.avoid_gatecut = false;
        }

        else if (tokens[0] == "FOLDING_STYLE") {
            setting.folding_style = tokens[1];
			std::cout << setting.folding_style << std::endl;
        }
        else if (tokens[0] == "REMOVE_SYM") {
            if (tokens[1] == "true") setting.remove_sym = true;
            else setting.remove_sym = false;
        }
        else if (tokens[0] == "REMOVE_DOM") {
            if (tokens[1] == "true") setting.remove_dom = true;
            else setting.remove_dom = false;
        }
        else if (tokens[0] == "BRANCH_BOUND") {
            if (tokens[1] == "true") setting.branch_bound = true;
            else setting.branch_bound = false;
        }
        else if (tokens[0] == "REFINE_SOL") {
            if (tokens[1] == "true") setting.refine_sol = true;
            else setting.refine_sol = false;
        }
        else if (tokens[0] == "M1_DIR") setting.m1_dir = tokens[1];
        else if (tokens[0] == "M2_DIR") setting.m2_dir = tokens[1];        
        else if (tokens[0] == "MIN_M2") {
            if (tokens[1] == "true") setting.min_m2 = true;
            else setting.min_m2 = false;
        }
        else if (tokens[0] == "MIN_M1") {
            if (tokens[1] == "true") setting.min_m1 = true;
            else setting.min_m1 = false;
        }
        else if (tokens[0] == "GEN_GDS") {
            if (tokens[1] == "true") setting.gen_gds = true;
            else setting.gen_gds = false;
        }
        else if (tokens[0] == "ROUTE_ACCEPT") setting.route_accept = std::stoi(tokens[1]);
        else {
            std::cout << "Error! Unidentified design rule: " << tokens[0] << std::endl;
            std::cout << "Error! Unidentified design rule: " << tokens[0] << std::endl;
        }
    }
    std::cout << setting.m1_dir << std::endl;
}

void make_IOnet(std::string outpath, Cell& cell){
    std::ofstream fout;
    //fout.open(outpath.string() + cell.name + ".txt");
	fs::path path = outpath / fs::path(cell.name + "_IOnet" + ".txt");
    std::cout<<"io path: "<<path<<std::endl;
    fout.open(path);

    fout << cell.name << std::endl;
    for(int i=0; i<cell.IOnets.size(); ++i){
        fout << cell.IOnets[i] << std::endl;
    }
    
    fout.close();
}


int main(int argc, char **argv) {

    ArgumentParser agparser(argc, argv);
    fs::path input_path, output_path, dr_path, route_path, gds_path;

    // Find DR
    const std::string &dr_name = agparser.getCmdOption("-d");
    if (!dr_name.empty()) dr_path = fs::current_path() / fs::path(dr_name);
    else dr_path = fs::current_path() / fs::path("input/dr/ASAP7_placement.dr");
    
    parsing_DR(dr_path);

    //fs::path ref_path = fs::path("/home/users/khbaek/CAD/csyn_fp/inputs/ours_SDFF_HD/cell");
    //run_reference(ref_path);

    //return 0;


    // Find input cdl
    const std::string &input_name = agparser.getCmdOption("-i");
    if (!input_name.empty()) input_path = fs::current_path() / fs::path(input_name);
    else input_path = fs::current_path() / fs::path("input/cdl/asap7.sp");
    
    Library l;
    cdlParser parser(l, input_path);
    parser.parse();


    // Specify output path
    const std::string &output_name = agparser.getCmdOption("-o");
    if (!output_name.empty()) output_path = fs::current_path() / fs::path(output_name);
    else output_path = fs::current_path() / fs::path("input/7.5Tdataset");
	std::cout << output_path << std::endl;
	if (!fs::exists(output_path)) fs::create_directories(output_path);

    route_path = output_path / fs::path("../route");
    std::cout << route_path << std::endl;
	fs::create_directories(route_path);

	gds_path = output_path / fs::path("../gds");
    std::cout << gds_path << std::endl;
    fs::create_directories(gds_path);

    int ncell = l.cells.size();

    std::cout << "The number of cells : " << l.cells.size() << std::endl;

    std::ofstream out(output_path.string() + "/summary.txt");

    for (int i = 0; i < ncell; i++) {
        //if (!(i == 52 || (i >= 65 && i <= 72) || i == 79 || (i >= 85 && i <= 87))) continue;
        Cell &temp = l.cells[i];

        //if (temp.name != "AO333x1_ASAP7_6t_R") continue;
		
        std::cout << output_path << std::endl;
        out << "(" << i << ") ";
        out << "Cell name : " << temp.name << std::endl;
        out << "The number of transistors = " << temp.trans.size() << std::endl;
        
        std::cout << "\n============================================" << std::endl;
        std::cout << "PMOS_MAX_FIN : " << setting.PMOSMaxAllowedFin << std::endl;
        std::cout << "NMOS_MAX_FIN : " << setting.NMOSMaxAllowedFin << std::endl;
        std::string db; 
        db = (setting.NetDiffGap == 1) ? "SDB" : "DDB";
        std::cout << "DIFF_BREAK : " << db << std::endl;
        std::cout << "XC_NUM : " << setting.XC << std::endl; 
        std::cout << "============================================\n" << std::endl;
        std::cout << "Cell name : " << temp.name << std::endl;
        

        //if (temp.trans.size() > 30) continue;
        //if (i >= 85 && i <= 87) continue; // skip ICG cells

        fs::path cell_output_path = output_path / fs::path(temp.name);
        fs::path cell_route_path = output_path / fs::path("../route");
        fs::path cell_gds_path = output_path / fs::path("../gds");
        //fs::create_directories(cell_output_path);
		//
        if (temp.trans.size() > 10) {
            std::cout<<'\n'<<"case1"<<'\n'<<std::endl;
            GroupPlacer placer(l.cells[i]);
			placer.out_dir = output_path;
            auto start = std::chrono::steady_clock::now();
            placer.run();
            auto end = std::chrono::steady_clock::now();
            out << "Min #CPP = " << placer.min_width + 2 << std::endl;
            //out << "The number of solutions = " << placer.solutions.size() << std::endl;
            out << "Placement time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            std::vector<int> group_pair(placer.numGroup, 0);
            for (auto& pair_list : placer.pairGroup) {
                group_pair[pair_list.second]++;
            }
            out << "#Groups = " << placer.numGroup << ", ";
            for (int i = 0; i < placer.numGroup; i++) out << group_pair[i] << " ";
            out << std::endl << std::endl;

			fs::path IOpath = output_path / fs::path("../IOnet/"); 
    		if(!fs::exists(IOpath)) fs::create_directories(IOpath);
            make_IOnet(IOpath, temp);

            //out << std::endl;
            
            /*
            // Save placements
            for (int width = placer.min_width; width <= placer.min_width + setting.relaxation; width++) {
                if (placer.solutions.find(width) != placer.solutions.end()) {
                    auto& w_solutions = placer.solutions[width];
                    int num_sol = w_solutions.size();
                    for (int k = 0; k < num_sol; k++) {
                        std::string output_file_name = "w" + std::to_string(width + 2);
                        fs::path output_file_path = cell_output_path / fs::path(output_file_name);  
                        fs::create_directories(output_file_path);

                        w_solutions[k].print_place(temp, output_file_path.string(), k);                      
                    }
                }
            }
            */

            // Routing
            for (int width = placer.min_width; width <= placer.min_width + setting.relaxation; width++) {
                //if (width - placer.min_width < 2) continue;
                if (placer.solutions.find(width) != placer.solutions.end()) {
                    auto& w_solutions = placer.solutions[width];
                    int num_sol = w_solutions.size();

                    bool is_routable = false;
                    bool is_m1_routable = false;
                    double min_m2_usage = 100000;
                    int64_t runtime = -1;

                    fs::path curw_best_gds_path;
                    
                    for (int k = 0; k < setting.routeSolutions; k++) {
                        //if (k >= setting.numSolutions) break;
						if (k >= num_sol) break;
                        std::cout << "Routing for solution " << k << " of width " << width + 2 << std::endl;

                        std::string output_file_name = temp.name + "_w" + std::to_string(width + 2) + "_" + std::to_string(k) + ".txt";
                        fs::path output_file_path = cell_route_path / fs::path(output_file_name);

                        Router router(l.cells[i], w_solutions[k]);
                        router.routing(output_file_path);

                        if (router.is_routable == false) {
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): Unroutable, Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;
                            //continue;
                        } 
                        else if (router.is_routable == true && router.m2_usage == 0) {
                            is_m1_routable = true;
                            is_routable = true;
                            min_m2_usage = 0;
                            curw_best_gds_path = output_file_path.replace_extension(fs::path(".gds"));
                            runtime = router.runtime;
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): M1 routable, Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;
                            break;
                        }
                        else {
                            is_routable = true;
                            if (router.m2_usage < min_m2_usage) {
                                min_m2_usage = router.m2_usage;
                                runtime = router.runtime;
                                curw_best_gds_path = output_file_path.replace_extension(fs::path(".gds"));
                            }
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): M2 routable (Usage " << router.m2_usage << "), Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;

                        }
                    }


                    if (is_routable) {
                        std::string cp_gds = "cp " + curw_best_gds_path.string() + " " + gds_path.string();
                        system(cp_gds.c_str());
                    }

                    if (is_m1_routable) break;
                }

            }
       }

       else { 
            std::cout<<'\n'<<"case2"<<'\n'<<std::endl;
            Placer placer(l.cells[i]);
			placer.out_dir = output_path;
            auto start = std::chrono::steady_clock::now();
            placer.run();
            auto end = std::chrono::steady_clock::now();
            out << "Min #CPP = " << placer.min_width + 2 << std::endl;
            //out << "The number of solutions = " << placer.solutions.size() << std::endl;
            out << "Placement time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
            //out << std::endl;

			fs::path IOpath = output_path / fs::path("../IOnet/"); 
			if(!fs::exists(IOpath)) fs::create_directories(IOpath);
            make_IOnet(IOpath, temp);

            /*
            // Save Placement
            for (int width = placer.min_width; width <= placer.min_width + setting.relaxation; width++) {
                if (placer.solutions.find(width) != placer.solutions.end()) {
                    auto& w_solutions = placer.solutions[width];
                    int num_sol = w_solutions.size();
                    for (int k = 0; k < num_sol; k++) {
                        std::string output_file_name = "w" + std::to_string(width + 2);
                        fs::path output_file_path = cell_output_path / fs::path(output_file_name);  
                        fs::create_directories(output_file_path);

                        w_solutions[k].print_place(temp, output_file_path.string(), k);                      
                    }
                }
            }*/
           
            // Routing
            for (int width = placer.min_width; width <= placer.min_width + setting.relaxation; width++) {
                //if (width != placer.min_width + setting.relaxation) continue;
                if (placer.solutions.find(width) != placer.solutions.end()) {
                    auto& w_solutions = placer.solutions[width];
                    int num_sol = w_solutions.size();

                    bool is_routable = false;
                    bool is_m1_routable = false;
                    double min_m2_usage = 100000;
                    int64_t runtime = -1;

                    fs::path curw_best_gds_path;


                    for (int k = 0; k < setting.routeSolutions; k++) {
						std::cout << num_sol << std::endl;
						if (k >= num_sol) break;
                        //if (k >= setting.numSolutions) break;

                        std::cout << "Routing for solution " << k << " of width " << width + 2 << std::endl;

                        std::string output_file_name = temp.name + "_w" + std::to_string(width + 2) + "_" + std::to_string(k) + ".txt";
                        fs::path output_file_path = cell_route_path / fs::path(output_file_name);

                        Router router(l.cells[i], w_solutions[k]);
                        router.routing(output_file_path);
                        std::cout << router.is_routable << std::endl;

                        if (router.is_routable == false) {
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): Unroutable, Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;
                            //continue;
                        } 
                        else if (router.is_routable == true && router.m2_usage == 0) {
                            is_m1_routable = true;
                            is_routable = true;

                            min_m2_usage = 0;
                            curw_best_gds_path = output_file_path.replace_extension(fs::path(".gds"));
                            runtime = router.runtime;
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): M1 routable, Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;
                            break;
                        }
                        else {
                            is_routable = true;
                            if (router.m2_usage < min_m2_usage) {
                                min_m2_usage = router.m2_usage;
                                runtime = router.runtime;
                                curw_best_gds_path = output_file_path.replace_extension(fs::path(".gds"));
                            }
                            out << "Width " << width + 2 << ", Solution " << k << " (Cost = " << w_solutions[k].cost  << "): M2 routable (Usage " << router.m2_usage << "), Routing time: " << router.runtime << "ms" << std::endl;
                            out << "[NOR_HPWL=" << w_solutions[k].nor_hpwl << ", MAX_H_GRID=" << w_solutions[k].max_h_grid << ", MAX_V_GRID=" << w_solutions[k].max_v_grid << ", MAX_H_COLUMN=" << w_solutions[k].max_h_column << ", MAX_V_COLUMN=" << w_solutions[k].max_v_column << ", MAX_H_ROW=" << w_solutions[k].max_h_row << ", MAX_V_ROW=" << w_solutions[k].max_v_row << std::endl << std::endl;

                        }
                    }
                    if (is_routable) {
                        std::string cp_gds = "cp " + curw_best_gds_path.string() + " " + gds_path.string();
                        system(cp_gds.c_str());
                    }

                    if (is_m1_routable) break;
                }
            }
       }
       out << std::endl;
    }
    return 0;
}
