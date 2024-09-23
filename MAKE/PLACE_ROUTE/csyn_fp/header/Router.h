#pragma once

#include "PlaceGrid.h"
#include "global.h"
#include "beol_data.h"
#include "RouteGrid.h"
#include "z3++.h"
#include "RoutingResult.h"

enum class routing_direction {BOTH, HOR, VER};
enum class ASAP_DR { GATE_PITCH = 54, GATE_WIDTH = 20, CELL_HEIGHT = 270, GATE_TIP_VER = 5, GCUT_HEIGHT = 44,
                     FIN_HEIGHT = 7, FIN_SPACING = 20, ACTIVE_UNIT = 27, MIN_ACTIVE_HEIGHT = 25, SDT_WIDTH = 24, LISD_WIDTH = 24,
                     LIG_PWR_HEIGHT = 16, LIG_CENTER_HEIGHT = 22, LIG_GATE = 1, V0_WIDTH = 18, M1_WIDTH = 18, M1_PITCH = 36, M1_V0_EX = 5, M1_T2T = 31, M1_T2S = 25};
enum class LAYER { WELL = 1, NSELECT = 12, PSELECT = 13, BOUNDARY = 100, P_SUB = 3, GATE = 7, GCUT = 10, FIN = 2, ACTIVE = 11, 
                   SDT = 88, LISD = 17, LIG = 16, V0 = 18, M1 = 19, V1 = 21, M2 = 20 };

class Router {
public:

    using Grid2D = std::vector<std::vector<int>>;
    using Grid3D = std::vector<std::vector<std::vector<int>>>;

    Router (Cell c, PlaceGrid s) : cell(c), place_sol(s) {
        grid = nullptr;
        grid_edge = nullptr;
        is_routable = false;
        m2_usage = 0;

        if (setting.m1_dir == "BOTH") M1 = routing_direction::BOTH;
        else if (setting.m1_dir == "HOR") M1 = routing_direction::HOR;
        else M1 = routing_direction::VER;

        if (setting.m2_dir == "BOTH") M2 = routing_direction::BOTH;
        else if (setting.m2_dir == "HOR") M2 = routing_direction::HOR;
        else M2 = routing_direction::VER;

    }

    ~Router();
    
    bool routing(fs::path output_path);

    void initialize_grid();
    void generate_pin_map();
    void add_detailed_routing_formulation (z3::context & c, z3::optimize & opt);

    z3::check_result solve_SMT (z3::optimize &opt);

    void gather_result (z3::context &c, z3::optimize &opt);
    void print_result (std::ofstream &out);

    void generate_ascii (std::ofstream &out, std::string cell_name);
    void ascii_to_gdsii (fs::path ascii_path);

    void DFS_Metal (std::shared_ptr<RoutingResult> route, std::vector<Point>& components, int y, int x, std::vector<std::vector<bool>>& explored, int metal_layer);


public:
    Cell cell;
    PlaceGrid place_sol;

    Grid_vertex** grid;	// 2D Vertex grid
	Grid_edge* grid_edge;	// Edge array

    std::unordered_map<std::string, bool**> pin_map, IO_pin_map;
    std::unordered_map<std::string, std::vector<std::vector<Point>>> floating_pins;
    std::unordered_map<std::string, std::vector<std::vector<Point>>> IO_floating_pins;
    
    std::unordered_map<std::string, std::shared_ptr<RoutingResult>> routing_result;

    std::vector<std::tuple<std::string, std::string, int, int, int>> mol_active;

    int row_size;
    int col_size;
    int num_layer;
    int edge_number;

    bool is_routable;
    double m2_usage;
    int64_t runtime;
	routing_direction M1, M2;
};