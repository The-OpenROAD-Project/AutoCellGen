#include "../header/Router.h"

Router::~Router() {

	for (int i = 0; i < row_size; i++) {
		if(sizeof(grid)/sizeof(Grid_vertex) == 0) break;
		delete [] grid[i];
	}
	
	delete [] grid;

	delete [] grid_edge;

	for (auto& pin : pin_map) {
		auto one_pin_map = pin.second;

		for (int i = 0; i < row_size; i++) delete [] one_pin_map[i];
		delete [] one_pin_map;

	}
}

void Router::initialize_grid() {
    row_size = 5;
	std::cout << "place sol : " << place_sol.cellWidth << std::endl;
    col_size = place_sol.cellWidth * 2 + 3; // +2 because dummy polies at both sides

	grid = new Grid_vertex*[row_size];
	for (int i = 0; i < row_size; i++) {
		grid[i] = new Grid_vertex[col_size];
		for (int j = 0; j < col_size; j++) {
			grid[i][j].row_index = i;
			grid[i][j].col_index = j;
		}
	}

	edge_number = (col_size - 1) * row_size + (row_size - 1) * col_size;	// #horizontal edge + #vertical edge
	grid_edge = new Grid_edge[edge_number];
	for (int i = 0; i < edge_number; i++) {
		grid_edge[i].index = i;
	}

	// Connect vertices and edges each other
	// Horizontal edge
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size - 1; j++) {
			int edge_idx = i*(col_size - 1) + j;

			// Connect edge to vertex
			grid[i][j].right_edge = &grid_edge[edge_idx];
			grid[i][j+1].left_edge = &grid_edge[edge_idx];
			
			// Connect vertices to edge
			grid_edge[edge_idx].connected_v[0] = &grid[i][j];
			grid_edge[edge_idx].connected_v[1] = &grid[i][j+1];
            grid_edge[edge_idx].capacity = 1;
		}
	}

	// Vertical edge
	for (int j = 0; j < col_size; j++) {
		for (int i = 0; i < row_size - 1; i++) {
			int edge_idx = (col_size - 1) * row_size + i*(col_size) + j;

			// Connect edge to vertex
			grid[i][j].bottom_edge = &grid_edge[edge_idx];
			grid[i+1][j].top_edge = &grid_edge[edge_idx];

			// Connect vertices to edge
			grid_edge[edge_idx].connected_v[0] = &grid[i][j];
			grid_edge[edge_idx].connected_v[1] = &grid[i+1][j];
            grid_edge[edge_idx].capacity = 1;

		}
	}

}

void Router::generate_pin_map() {

	// connect the same net of gate polies by LIG
	// Generate pin map per pin to be connected by M1, M2
	// Save floating pins to floating_pins variable

	std::vector<std::string> net_list;
	for (auto net : cell.nets) {
		if (std::find(net_list.begin(), net_list.end(), net) == net_list.end()) {
			net_list.push_back(net);
		}
	}
	for (auto net : cell.IOnets) {
		if (std::find(net_list.begin(), net_list.end(), net) == net_list.end()) {
			net_list.push_back(net);
		}
	}

	std::vector<std::string> gate_poly;
	std::vector<std::string> gate_net_list;
	for (int i = 0; i < place_sol.cellWidth; i++) {
		std::string net = (place_sol.pmos[i].gate != "dummy") ? place_sol.pmos[i].gate : place_sol.nmos[i].gate;
		gate_poly.push_back(net);

		if (net != "dummy" && std::find(gate_net_list.begin(), gate_net_list.end(), net) == gate_net_list.end()) {
			gate_net_list.push_back(net);
		}

	}

	// find consecutive gates (Connected by LIG)
	std::vector<std::tuple<std::string, int, int>> connected_gates;
	int pos_start = -1;
	std::string cur_net = "initial";
	for (int i = 0; i < place_sol.cellWidth; i++) {
		//if (gate_poly[i] == "dummy") continue;
		if (pos_start == -1) {
			pos_start = i;
			cur_net = gate_poly[i];
		}
		else if (gate_poly[i] != cur_net) {
			// pos_start ~ i - 1
			if (cur_net != "dummy") connected_gates.push_back(std::make_tuple(cur_net, pos_start, i - 1));
			cur_net = gate_poly[i];
			pos_start = i;
		}
		if (i == place_sol.cellWidth - 1) {
			if (cur_net != "dummy") connected_gates.push_back(std::make_tuple(cur_net, pos_start, i));
			break;
		}
	}


	for (auto net : net_list) {
		if (net == "VDD" || net == "VSS") continue;
		int num_pins = 0;

		std::vector<std::vector<Point>> float_point_list;
		std::vector<Point> float_points;
		float_point_list.clear();
		float_points.clear();

		// find consecutive gates
		for (auto& connected_info : connected_gates) {
			std::string cur_net = std::get<0>(connected_info);
			if (net != cur_net) continue;
			int lx = std::get<1>(connected_info);
			int rx = std::get<2>(connected_info);

			float_points.clear();
			for (int i = lx; i <= rx; i++) {
				float_points.emplace_back(2, 2 * i + 2);
				if (i != rx) float_points.emplace_back(2, 2 * i + 3);
			}
			float_point_list.push_back(float_points);
			num_pins++;
		}

		// find active region + LISD-connected actives 
		std::vector<std::pair<int, int>> pmos_net, nmos_net; // x-loc, nfin

		for (int i = 0; i < place_sol.cellWidth; i++) {
			if (place_sol.pmos[i].left == net) {
				pmos_net.push_back(std::make_pair(i, place_sol.pmos[i].nfin));
				num_pins++;
			}
			if (i > 0 && place_sol.pmos[i].gate == "dummy" && place_sol.pmos[i - 1].right == net) {
				pmos_net.push_back(std::make_pair(i, place_sol.pmos[i - 1].nfin));
				num_pins++;			
			}
			if (i == place_sol.cellWidth - 1 && place_sol.pmos[i].right == net) {
				pmos_net.push_back(std::make_pair(i + 1, place_sol.pmos[i].nfin));
				num_pins++;
			}

			if (place_sol.nmos[i].left == net) {
				nmos_net.push_back(std::make_pair(i, place_sol.nmos[i].nfin));
				num_pins++;
			}
			if (i > 0 && place_sol.nmos[i].gate == "dummy" && place_sol.nmos[i - 1].right == net) {
				nmos_net.push_back(std::make_pair(i, place_sol.nmos[i - 1].nfin));
				num_pins++;	
			}
			if (i == place_sol.cellWidth - 1 && place_sol.nmos[i].right == net) {
				nmos_net.push_back(std::make_pair(i + 1, place_sol.nmos[i].nfin));
				num_pins++;
			}

		}

		int n_pmos = static_cast<int>(pmos_net.size());
		int n_nmos = static_cast<int>(nmos_net.size());

		std::vector<bool> satisfied;
		for (int i = 0; i < n_pmos - 1; i++) {
			if (pmos_net[i + 1].first - pmos_net[i].first == 1 && pmos_net[i + 1].second == pmos_net[i].second) {
				satisfied.push_back(true);
				num_pins--;
			}
			else satisfied.push_back(false);
		}

		int start = -1;
		bool continuous = false;
		for (int i = 0; i < satisfied.size(); i++) {
			if (satisfied[i]) {
				if (!continuous) {
					continuous = true;
					start = i;
				}
				if (i == satisfied.size() - 1 && continuous) {
					mol_active.push_back(std::make_tuple(net, "p", pmos_net[start].second, pmos_net[start].first, pmos_net[i + 1].first));
				}
			}
			else {
				if (continuous) {
					mol_active.push_back(std::make_tuple(net, "p", pmos_net[start].second, pmos_net[start].first, pmos_net[i].first));
					continuous = false;
				}
			}
		}

		satisfied.clear();
		for (int i = 0; i < n_nmos - 1; i++) {
			if (nmos_net[i + 1].first - nmos_net[i].first == 1 && nmos_net[i + 1].second == nmos_net[i].second) {
				satisfied.push_back(true);
				num_pins--;
			}
			else satisfied.push_back(false);
		}

		start = -1;
		continuous = false;
		for (int i = 0; i < satisfied.size(); i++) {
			if (satisfied[i]) {
				if (!continuous) {
					continuous = true;
					start = i;
				}
				if (i == satisfied.size() - 1 && continuous) {
					mol_active.push_back(std::make_tuple(net, "n", nmos_net[start].second, nmos_net[start].first, nmos_net[i + 1].first));
				}
			}
			else {
				if (continuous) {
					mol_active.push_back(std::make_tuple(net, "n", nmos_net[start].second, nmos_net[start].first, nmos_net[i].first));
					continuous = false;
				}
			}
		}


		std::cout << "The number of pin for net " << net << ": " << num_pins << std::endl;

		if (num_pins > 1) {
			// Allocate memory for pin map and initialize it
			bool** pin_map_of_cur_net = new bool*[row_size];
			for (int j = 0; j < row_size; j++) {
				pin_map_of_cur_net[j] = new bool[col_size];
				for (int k = 0; k < col_size; k++) {
					pin_map_of_cur_net[j][k] = false;
				}
			}

			// allocate LIG floating pins
			if (float_point_list.size() > 0) {
				for (auto& floating_points : float_point_list) {
					for (auto& floating_point : floating_points) {
						pin_map_of_cur_net[floating_point.y][floating_point.x] = true;
					}
				}
			}

			// allocate S/G/D floating pins
			// allocate LISD-connected active first
			for (auto& mol_active_info : mol_active) {
				std::string net_name = std::get<0>(mol_active_info);
				if (net != net_name) continue;

				std::string region = std::get<1>(mol_active_info);
				int nfin = std::get<2>(mol_active_info);
				int lx = std::get<3>(mol_active_info);
				int rx = std::get<4>(mol_active_info);

				float_points.clear();
				for (int i = 2 * lx + 1; i <= 2 * rx + 1; i += 2) {
					if (region == "p") {
						pin_map_of_cur_net[0][i] = true;
						float_points.emplace_back(0, i);
						if (nfin > 1) {
							pin_map_of_cur_net[1][i] = true;
							float_points.emplace_back(1, i);
						}
					}
					if (region == "n") {
						pin_map_of_cur_net[4][i] = true;
						float_points.emplace_back(4, i);
						if (nfin > 1) {
							pin_map_of_cur_net[3][i] = true;
							float_points.emplace_back(3, i);
						}
					}
				}
				float_point_list.push_back(float_points);
			}

			// allocate LISD-unconnected active regions
			// PMOS
			for (auto& pmos_active : pmos_net) {
				int x_loc = pmos_active.first;
				int act_fin = pmos_active.second;
				bool not_contained = true;

				for (auto& mol_active_info : mol_active) {
					std::string net_name = std::get<0>(mol_active_info);
					if (net != net_name) continue;
	
					std::string region = std::get<1>(mol_active_info);
					if (region != "p") continue;

					int lx = std::get<3>(mol_active_info);
					int rx = std::get<4>(mol_active_info);		
					if (x_loc >= lx && x_loc <= rx) {
						not_contained = false;
						break;
					}
				}
				if (not_contained) {
					float_points.clear();
					pin_map_of_cur_net[0][2 * x_loc + 1] = true;
					float_points.emplace_back(0, 2 * x_loc + 1);
					if (act_fin > 1) {
						pin_map_of_cur_net[1][2 * x_loc + 1] = true;
						float_points.emplace_back(1, 2 * x_loc + 1);
					}				
					float_point_list.push_back(float_points);
				}
			}
			
			// NMOS
			for (auto& nmos_active : nmos_net) {
				int x_loc = nmos_active.first;
				int act_fin = nmos_active.second;
				bool not_contained = true;

				for (auto& mol_active_info : mol_active) {
					std::string net_name = std::get<0>(mol_active_info);
					if (net != net_name) continue;
	
					std::string region = std::get<1>(mol_active_info);
					if (region != "n") continue;

					int lx = std::get<3>(mol_active_info);
					int rx = std::get<4>(mol_active_info);		
					if (x_loc >= lx && x_loc <= rx) {
						not_contained = false;
						break;
					}
				}
				if (not_contained) {
					float_points.clear();
					pin_map_of_cur_net[4][2 * x_loc + 1] = true;
					float_points.emplace_back(4, 2 * x_loc + 1);
					if (act_fin > 1) {
						pin_map_of_cur_net[3][2 * x_loc + 1] = true;
						float_points.emplace_back(3, 2 * x_loc + 1);
					}
					float_point_list.push_back(float_points);
				}
			}

			pin_map[net] = pin_map_of_cur_net;
			floating_pins[net] = float_point_list;
		}
		else if (num_pins == 1 && std::find(cell.IOnets.begin(), cell.IOnets.end(), net) != cell.IOnets.end()) {  // IOpin -> connected gates
			// Allocate memory for pin map and initialize it
			bool** pin_map_of_cur_net = new bool*[row_size];
			for (int j = 0; j < row_size; j++) {
				pin_map_of_cur_net[j] = new bool[col_size];
				for (int k = 0; k < col_size; k++) {
					pin_map_of_cur_net[j][k] = false;
				}
			}

			// allocate LIG floating pins
			if (float_point_list.size() > 0) {
				for (auto& floating_points : float_point_list) {
					for (auto& floating_point : floating_points) {
						pin_map_of_cur_net[floating_point.y][floating_point.x] = true;
					}
				}
			}

			IO_pin_map[net] = pin_map_of_cur_net;
			IO_floating_pins[net] = float_point_list;

		}
	}
	// Print pin_map
	/*
	for (auto& iter : pin_map) {
		std::cout << "Net " << iter.first << std::endl;
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				std::cout << iter.second[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		
		auto& floating_points = floating_pins[iter.first];
		for (auto& fp_list : floating_points) {
			for (auto& fp : fp_list) {
				std::cout << "(" << fp.y << ", " << fp.x << ") ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	*/

}


void Router::add_detailed_routing_formulation(z3::context & c, z3::optimize & opt) {

	// Variables for detailed routing
	// metal routing map (x, y, z, n)1
	z3::expr_vector metal_grid(c);

	z3::expr_vector hor_grid(c);
	z3::expr_vector ver_grid(c);
	z3::expr_vector via_grid(c);

	int track_num = 5;
	int num_net_to_connect = 0;
	int layer_num = 2;
	num_layer = layer_num;

	//routing_direction M1 = routing_direction::BOTH;
	//routing_direction M2 = routing_direction::HOR;
	//routing_direction M3 = routing_direction::HOR;

	std::vector<routing_direction> metal_dir;
	metal_dir.push_back(M1);
	metal_dir.push_back(M2);
	//metal_dir.push_back(M3);


	auto idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * track_num * col_size + z * track_num * col_size + y * col_size + x;
	};

	// generate grid (metal_grid)
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string metal_name = iter.first + "_(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					
					metal_grid.push_back(c.int_const(metal_name.c_str()));
					opt.add(metal_grid[idx(x, y, z, num_net_to_connect)] >= 0 && metal_grid[idx(x, y, z, num_net_to_connect)] <= 1);

				}
			}
		}
		num_net_to_connect++;
	}	
	// hor_grid
	auto h_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * track_num * (col_size - 1) + z * track_num * (col_size - 1) + y * (col_size - 1) + x;
	};
	int n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size - 1; x++) {
					std::string hor_name = iter.first + "_h(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					hor_grid.push_back(c.int_const(hor_name.c_str()));

					if (metal_dir[z] == routing_direction::HOR || metal_dir[z] == routing_direction::BOTH) {
						opt.add(hor_grid[h_idx(x, y, z, n)] >= 0 && hor_grid[h_idx(x, y, z, n)] <= 1);
						//opt.add(z3::implies(hor_grid[h_idx(x, y, z, n)] == 1, metal_grid[idx(x, y, z, n)] == 1 && metal_grid[idx(x + 1, y, z, n)] == 1));
					}
					else { // Vertical
						opt.add(hor_grid[h_idx(x, y, z, n)] == 0);
					}
				}
			}
		}		
		n++;
	}

	// ver_grid
	auto v_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * (track_num - 1) * col_size + z * (track_num - 1) * col_size + y * col_size + x;
	};
	n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num - 1; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string ver_name = iter.first + "_v(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					ver_grid.push_back(c.int_const(ver_name.c_str()));

					if (metal_dir[z] == routing_direction::VER || metal_dir[z] == routing_direction::BOTH) {
						opt.add(ver_grid[v_idx(x, y, z, n)] >= 0 && ver_grid[v_idx(x, y, z, n)] <= 1);
						//opt.add(z3::implies(ver_grid[v_idx(x, y, z, n)] == 1, metal_grid[idx(x, y, z, n)] == 1 && metal_grid[idx(x, y + 1, z, n)] == 1));
					}
					else opt.add(ver_grid[v_idx(x, y, z, n)] == 0);
				}
			}
		}		
		n++;
	}

	// via_grid
	auto i_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * (layer_num - 1) * track_num * col_size + z * track_num * col_size + y * col_size + x;
	};
	n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num - 1; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string via_name = iter.first + "_i(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					via_grid.push_back(c.int_const(via_name.c_str()));

					opt.add(via_grid[i_idx(x, y, z, n)] >= 0 && via_grid[i_idx(x, y, z, n)] <= 1);
					//opt.add(z3::implies(via_grid[i_idx(x, y, z, n)] == 1, metal_grid[idx(x, y, z, n)] == 1 && metal_grid[idx(x, y, z + 1, n)] == 1));
				}
			}
		}		
		n++;
	}

	// Metal grid definition
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					z3::expr adjacent = c.int_val(0);
					// HOR_LEFT (not VER layer)
					if (x > 0 && metal_dir[z] != routing_direction::VER) 
						adjacent = adjacent + hor_grid[h_idx(x - 1, y, z, n)];
					// HOR_RIGHT (not VER layer)
					if (x < col_size - 1 && metal_dir[z] != routing_direction::VER) 
						adjacent = adjacent + hor_grid[h_idx(x, y, z, n)];
					// VER_TOP (not HOR layer)
					if (y > 0 && metal_dir[z] != routing_direction::HOR) 
						adjacent = adjacent + ver_grid[v_idx(x, y - 1, z, n)];
					// VER_BOTTOM (not HOR layer)
					if (y < track_num - 1 && metal_dir[z] != routing_direction::HOR) 
						adjacent = adjacent + ver_grid[v_idx(x, y, z, n)];
					// VIA_UP OR VIA_DOWN
					adjacent = adjacent + via_grid[i_idx(x, y, 0, n)];

					opt.add(z3::ite(adjacent == 0, metal_grid[idx(x, y, z, n)] == 0, metal_grid[idx(x, y, z, n)] == 1));
				}
			}
		}
	}



	// 2. Vertex exclusiveness
	for (int z = 0; z < layer_num; z++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				z3::expr occupied = c.int_val(0);
				for (int n = 0; n < num_net_to_connect; n++) {
					occupied = occupied + metal_grid[idx(x, y, z, n)];
				}
				opt.add(occupied <= 1);
			}
		}
	}

	auto check_fp = [](std::vector<Point>& pin_list, Point pin) {
		int index = 0;
		for (auto& pin_point : pin_list) {
			if (pin_point == pin) break;
			index++;
		}
		return index;
	};


	// 3. Connectivity constraints
	int n_idx = 0;
	for (auto& iter : floating_pins) {
		auto pin_name = iter.first;
		auto& floating_pin_list = iter.second;

		if (floating_pin_list.size() == 2) {
			auto& source_pin = floating_pin_list[0];
			auto& dest_pin = floating_pin_list[1];

			int n_source_point = source_pin.size();
			int n_dest_point = dest_pin.size();

			z3::expr_vector source_edge(c);
			z3::expr_vector dest_edge(c);

			int s_i = 0;
			for (auto& s_pin : source_pin) {
				std::string point_name = pin_name + "_source_0_(" + std::to_string(s_pin.x) + ", " + std::to_string(s_pin.y) + ")";
				source_edge.push_back(c.int_const(point_name.c_str()));

				opt.add(source_edge[s_i] >= 0 && source_edge[s_i] <= 1);
				//opt.add(z3::implies(source_edge[s_i] == 1, metal_grid[idx(s_pin.x, s_pin.y, 0, n_idx)]));
				s_i++;
			}
			int d_i = 0;
			for (auto& d_pin : dest_pin) {
				std::string point_name = pin_name + "_dest_0_(" + std::to_string(d_pin.x) + ", " + std::to_string(d_pin.y) + ")";
				dest_edge.push_back(c.int_const(point_name.c_str()));

				opt.add(dest_edge[d_i] >= 0 && dest_edge[d_i] <= 1);
				//opt.add(z3::implies(dest_edge[d_i] == 1, metal_grid[idx(d_pin.x, d_pin.y, 0, n_idx)]));
				d_i++;				
			}
			/* CONSTRAIN same active net routing */
			
			int lx = 999, rx = -1;
			bool source_all_pmos = true, source_all_nmos = true;
			bool dest_all_pmos = true, dest_all_nmos = true;
			for (auto& source_point : source_pin) {
				if (source_point.x < lx) lx = source_point.x;
				if (source_point.x > rx) rx = source_point.x;
				if (!(source_point.y == 0 || source_point.y == 1)) source_all_pmos = false;
				if (!(source_point.y == 5 || source_point.y == 6)) source_all_nmos = false;
			}
			for (auto& dest_point : dest_pin) {
				if (dest_point.x < lx) lx = dest_point.x;
				if (dest_point.x > rx) rx = dest_point.x;
				if (!(dest_point.y == 0 || dest_point.y == 1)) dest_all_pmos = false;
				if (!(dest_point.y == 5 || dest_point.y == 6)) dest_all_nmos = false;
			}

			if (source_all_nmos && dest_all_nmos) { // both in NMOS
				assert(!source_all_pmos && !dest_all_pmos);
				// hor grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size - 1; x++) {
							if ((x >= lx && x <= rx - 1) && (y >= 5 && y <= 6)) continue;
							opt.add(hor_grid[h_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
				// ver grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num - 1; y++) {
						for (int x = 0; x < col_size; x++) {
							if ((x >= lx && x <= rx) && (y == 5)) continue;
							opt.add(ver_grid[v_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
				// via grid restriction
				for (int z = 0; z < layer_num - 1; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size; x++) {
							if ((x >= lx && x <= rx) && (y >= 5 && y <= 6)) continue;
							opt.add(via_grid[i_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
			}

			else if (source_all_pmos && dest_all_pmos) { // both in PMOS
				assert(!source_all_nmos && !dest_all_nmos);
				// hor grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size - 1; x++) {
							if ((x >= lx && x <= rx - 1) && (y >= 0 && y <= 1)) continue;
							opt.add(hor_grid[h_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
				// ver grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num - 1; y++) {
						for (int x = 0; x < col_size; x++) {
							if ((x >= lx && x <= rx) && (y == 0)) continue;
							opt.add(ver_grid[v_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
				// via grid restriction
				for (int z = 0; z < layer_num - 1; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size; x++) {
							if ((x >= lx && x <= rx) && (y >= 0 && y <= 1)) continue;
							opt.add(via_grid[i_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
			}
			// Constrain routing region into acceptance field
			else {
				// hor grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size - 1; x++) {
							if (x >= lx - setting.route_accept && x <= rx - 1 + setting.route_accept) continue;
							opt.add(hor_grid[h_idx(x, y, z, n_idx)] == 0);
						}
					}
				}					

				// ver grid restriction
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num - 1; y++) {
						for (int x = 0; x < col_size; x++) {
							if (x >= lx - setting.route_accept && x <= rx + setting.route_accept) continue;
							opt.add(ver_grid[v_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
				// via grid restriction
				for (int z = 0; z < layer_num - 1; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size; x++) {
							if (x >= lx - setting.route_accept && x <= rx + setting.route_accept) continue;
							opt.add(via_grid[i_idx(x, y, z, n_idx)] == 0);
						}
					}
				}
			}			
			/* END OF RESTRICTION */



			// Grid nodes (flow == 0 or 2)
			for (int z = 0; z < layer_num; z++) {
				for (int y = 0; y < track_num; y++) {
					for (int x = 0; x < col_size; x++) {
						int index = idx(x, y, z, n_idx);
						z3::expr adjacent = c.int_val(0);
						// HOR_LEFT (not VER layer)
						if (x > 0 && metal_dir[z] != routing_direction::VER) 
							adjacent = adjacent + hor_grid[h_idx(x - 1, y, z, n_idx)];
						// HOR_RIGHT (not VER layer)
						if (x < col_size - 1 && metal_dir[z] != routing_direction::VER) 
							adjacent = adjacent + hor_grid[h_idx(x, y, z, n_idx)];
						// VER_TOP (not HOR layer)
						if (y > 0 && metal_dir[z] != routing_direction::HOR) 
							adjacent = adjacent + ver_grid[v_idx(x, y - 1, z, n_idx)];
						// VER_BOTTOM (not HOR layer)
						if (y < track_num - 1 && metal_dir[z] != routing_direction::HOR) 
							adjacent = adjacent + ver_grid[v_idx(x, y, z, n_idx)];
						// VIA_UP OR VIA_DOWN
						adjacent = adjacent + via_grid[i_idx(x, y, 0, n_idx)];

						if (z == 0 && check_fp(source_pin, Point(y, x)) < n_source_point) {
							int p_i = check_fp(source_pin, Point(y, x));
							adjacent = adjacent + source_edge[p_i];
						}
						else if (z == 0 && check_fp(dest_pin, Point(y, x)) < n_dest_point) {
							int p_i = check_fp(dest_pin, Point(y, x));
							adjacent = adjacent + dest_edge[p_i];
						}
						opt.add(adjacent == 0 || adjacent == 2);
					}
				}
			}

			// Supernodes (flow == 1)
			z3::expr adjacent = c.int_val(0);
			for (int i = 0; i < s_i; i++) {
				adjacent = adjacent + source_edge[i];
			}
			opt.add(adjacent == 1);

			adjacent = c.int_val(0);
			for (int i = 0; i < d_i; i++) {
				adjacent = adjacent + dest_edge[i];
			}
			opt.add(adjacent == 1);


		}
		else {
			// ************* TODO (Multi-pin) ********************

			auto& source_pin = floating_pin_list[0];
			int num_dest_pins = floating_pin_list.size() - 1;

			z3::expr_vector multi_hor_grid(c);
			z3::expr_vector multi_ver_grid(c);
			z3::expr_vector multi_via_grid(c);

			// flow horizontal grid
			auto m_h_idx = [&](int x, int y, int z, int d_idx) {
					return d_idx * layer_num * track_num * (col_size - 1) + z * track_num * (col_size - 1) + y * (col_size - 1) + x;
			};
			for (int d = 0; d < num_dest_pins; d++) {
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size - 1; x++) {
							std::string hor_name = pin_name + "_" + std::to_string(d) + "_h(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
							multi_hor_grid.push_back(c.int_const(hor_name.c_str()));

							if (metal_dir[z] == routing_direction::HOR || metal_dir[z] == routing_direction::BOTH) {
								opt.add(multi_hor_grid[m_h_idx(x, y, z, d)] >= 0 && multi_hor_grid[m_h_idx(x, y, z, d)] <= 1);
								//opt.add(z3::implies(multi_hor_grid[m_h_idx(x, y, z, d)] == 1, hor_grid[h_idx(x, y, z, n_idx)] == 1));
							}
							else opt.add(multi_hor_grid[m_h_idx(x, y, z, d)] == 0);
						}
					}
				}
			}
			for (int z = 0; z < layer_num; z++) {
				for (int y = 0; y < track_num; y++) {
					for (int x = 0; x < col_size - 1; x++) {
						z3::expr sum = c.int_val(0);
						for (int d = 0; d < num_dest_pins; d++) {
							sum = sum + multi_hor_grid[m_h_idx(x, y, z, d)];
						}
						opt.add(z3::ite(sum == 0, hor_grid[h_idx(x, y, z, n_idx)] == 0, hor_grid[h_idx(x, y, z, n_idx)] == 1));
					}
				}
			}



			// flow vertical grid
			auto m_v_idx = [&](int x, int y, int z, int d_idx) {
				return d_idx * layer_num * (track_num - 1) * col_size + z * (track_num - 1) * col_size + y * col_size + x;
			};
			for (int d = 0; d < num_dest_pins; d++) {
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num - 1; y++) {
						for (int x = 0; x < col_size; x++) {
							std::string ver_name = pin_name + "_" + std::to_string(d) + "_v(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
							multi_ver_grid.push_back(c.int_const(ver_name.c_str()));

							if (metal_dir[z] == routing_direction::VER || metal_dir[z] == routing_direction::BOTH) {
								opt.add(multi_ver_grid[m_v_idx(x, y, z, d)] >= 0 && multi_ver_grid[m_v_idx(x, y, z, d)] <= 1);							
								//opt.add(z3::implies(multi_ver_grid[m_v_idx(x, y, z, d)] == 1, ver_grid[v_idx(x, y, z, n_idx)] == 1));
							}
							else opt.add(multi_ver_grid[m_v_idx(x, y, z, d)] == 0);
						}
					}
				}
			}
			for (int z = 0; z < layer_num; z++) {
				for (int y = 0; y < track_num - 1; y++) {
					for (int x = 0; x < col_size; x++) {
						z3::expr sum = c.int_val(0);
						for (int d = 0; d < num_dest_pins; d++) {
							sum = sum + multi_ver_grid[m_v_idx(x, y, z, d)];
						}
						opt.add(z3::ite(sum == 0, ver_grid[v_idx(x, y, z, n_idx)] == 0, ver_grid[v_idx(x, y, z, n_idx)] == 1));
					}
				}
			}

			// flow via grid
			auto m_i_idx = [&](int x, int y, int z, int d_idx) {
				return d_idx * (layer_num - 1) * track_num * col_size + z * track_num * col_size + y * col_size + x;
			};
			for (int d = 0; d < num_dest_pins; d++) {
				for (int z = 0; z < layer_num - 1; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size; x++) {
							std::string via_name = pin_name + "_" + std::to_string(d) + "_i(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
							multi_via_grid.push_back(c.int_const(via_name.c_str()));

							opt.add(multi_via_grid[m_i_idx(x, y, z, d)] >= 0 && multi_via_grid[m_i_idx(x, y, z, d)] <= 1);
							opt.add(z3::implies(multi_via_grid[m_i_idx(x, y, z, d)] == 1, via_grid[i_idx(x, y, z, n_idx)] == 1));
						}
					}
				}
			}
			for (int z = 0; z < layer_num - 1; z++) {
				for (int y = 0; y < track_num; y++) {
					for (int x = 0; x < col_size; x++) {
						z3::expr sum = c.int_val(0);
						for (int d = 0; d < num_dest_pins; d++) {
							sum = sum + multi_via_grid[m_i_idx(x, y, z, d)];
						}
						opt.add(z3::ite(sum == 0, via_grid[i_idx(x, y, z, n_idx)] == 0, via_grid[i_idx(x, y, z, n_idx)] == 1));
					}
				}
			}

			// Connectivity for each flow
			for (int d = 0; d < num_dest_pins; d++) {
				auto& dest_pin = floating_pin_list[d + 1];

				int n_source_point = source_pin.size();
				int n_dest_point = dest_pin.size();

				z3::expr_vector source_edge(c);
				z3::expr_vector dest_edge(c);

				int s_i = 0;
				for (auto& s_pin : source_pin) {
					std::string point_name = pin_name + "_source_" + std::to_string(d) + "_(" + std::to_string(s_pin.x) + ", " + std::to_string(s_pin.y) + ")";
					source_edge.push_back(c.int_const(point_name.c_str()));

					opt.add(source_edge[s_i] >= 0 && source_edge[s_i] <= 1);
					s_i++;
				}

				int d_i = 0;
				for (auto& d_pin : dest_pin) {
					std::string point_name = pin_name + "_dest_" + std::to_string(d) + "_(" + std::to_string(d_pin.x) + ", " + std::to_string(d_pin.y) + ")";
					dest_edge.push_back(c.int_const(point_name.c_str()));

					opt.add(dest_edge[d_i] >= 0 && dest_edge[d_i] <= 1);
					//opt.add(z3::implies(dest_edge[d_i] == 1, metal_grid[idx(d_pin.x, d_pin.y, 0, n_idx)]));
					d_i++;				
				}

				/* CONSTRAIN same active net routing */
				
				int lx = 999, rx = -1;
				bool source_all_pmos = true, source_all_nmos = true;
				bool dest_all_pmos = true, dest_all_nmos = true;
				for (auto& source_point : source_pin) {
					if (source_point.x < lx) lx = source_point.x;
					if (source_point.x > rx) rx = source_point.x;
					if (!(source_point.y == 0 || source_point.y == 1)) source_all_pmos = false;
					if (!(source_point.y == 5 || source_point.y == 6)) source_all_nmos = false;
				}
				for (auto& dest_point : dest_pin) {
					if (dest_point.x < lx) lx = dest_point.x;
					if (dest_point.x > rx) rx = dest_point.x;
					if (!(dest_point.y == 0 || dest_point.y == 1)) dest_all_pmos = false;
					if (!(dest_point.y == 5 || dest_point.y == 6)) dest_all_nmos = false;
				}

				if (source_all_nmos && dest_all_nmos) { // both in NMOS
					assert(!source_all_pmos && !dest_all_pmos);
					// hor grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size - 1; x++) {
								if ((x >= lx && x <= rx - 1) && (y >= 5 && y <= 6)) continue;
								opt.add(multi_hor_grid[m_h_idx(x, y, z, d)] == 0);
							}
						}
					}
					// ver grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num - 1; y++) {
							for (int x = 0; x < col_size; x++) {
								if ((x >= lx && x <= rx) && (y == 5)) continue;
								opt.add(multi_ver_grid[m_v_idx(x, y, z, d)] == 0);
							}
						}
					}
					// via grid restriction
					for (int z = 0; z < layer_num - 1; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size; x++) {
								if ((x >= lx && x <= rx) && (y >= 5 && y <= 6)) continue;
								opt.add(multi_via_grid[m_i_idx(x, y, z, d)] == 0);
							}
						}
					}
				}

				else if (source_all_pmos && dest_all_pmos) { // both in PMOS
					assert(!source_all_nmos && !dest_all_nmos);
					int lx = 999, rx = -1;
					for (auto& source_point : source_pin) {
						if (source_point.x < lx) lx = source_point.x;
						if (source_point.x > rx) rx = source_point.x;
					}
					for (auto& dest_point : dest_pin) {
						if (dest_point.x < lx) lx = dest_point.x;
						if (dest_point.x > rx) rx = dest_point.x;
					}
					// hor grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size - 1; x++) {
								if ((x >= lx && x <= rx - 1) && (y >= 0 && y <= 1)) continue;
								opt.add(multi_hor_grid[m_h_idx(x, y, z, d)] == 0);
							}
						}
					}
					// ver grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num - 1; y++) {
							for (int x = 0; x < col_size; x++) {
								if ((x >= lx && x <= rx) && (y == 0)) continue;
								opt.add(multi_ver_grid[m_v_idx(x, y, z, d)] == 0);
							}
						}
					}
					// via grid restriction
					for (int z = 0; z < layer_num - 1; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size; x++) {
								if ((x >= lx && x <= rx) && (y >= 0 && y <= 1)) continue;
								opt.add(multi_via_grid[m_i_idx(x, y, z, d)] == 0);
							}
						}
					}
				}
				// Constrain routing region into acceptance field
				else {
					// hor grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size - 1; x++) {
								if (x >= lx - setting.route_accept && x <= rx - 1 + setting.route_accept) continue;
								opt.add(multi_hor_grid[m_h_idx(x, y, z, d)] == 0);
							}
						}
					}					

					// ver grid restriction
					for (int z = 0; z < layer_num; z++) {
						for (int y = 0; y < track_num - 1; y++) {
							for (int x = 0; x < col_size; x++) {
								if (x >= lx - setting.route_accept && x <= rx + setting.route_accept) continue;
								opt.add(multi_ver_grid[m_v_idx(x, y, z, d)] == 0);
							}
						}
					}
					// via grid restriction
					for (int z = 0; z < layer_num - 1; z++) {
						for (int y = 0; y < track_num; y++) {
							for (int x = 0; x < col_size; x++) {
								if (x >= lx - setting.route_accept && x <= rx + setting.route_accept) continue;
								opt.add(multi_via_grid[m_i_idx(x, y, z, d)] == 0);
							}
						}
					}
				}
				
				/* END OF RESTRICTION */



				// Grid nodes (flow == 0 or 2)
				for (int z = 0; z < layer_num; z++) {
					for (int y = 0; y < track_num; y++) {
						for (int x = 0; x < col_size; x++) {
							z3::expr adjacent = c.int_val(0);
							// HOR_LEFT
							if (x > 0 && metal_dir[z] != routing_direction::VER) 
								adjacent = adjacent + multi_hor_grid[m_h_idx(x - 1, y, z, d)];
							// HOR_RIGHT
							if (x < col_size - 1 && metal_dir[z] != routing_direction::VER) 
								adjacent = adjacent + multi_hor_grid[m_h_idx(x, y, z, d)]; 
							// VER_TOP (only M1)
							if (y > 0 && metal_dir[z] != routing_direction::HOR) 
								adjacent = adjacent + multi_ver_grid[m_v_idx(x, y - 1, z, d)];
							// VER_BOT (only M1)
							if (y < track_num - 1 && metal_dir[z] != routing_direction::HOR) 
								adjacent = adjacent + multi_ver_grid[m_v_idx(x, y, z, d)];
							// VIA_UP or VIA_DOWN
							adjacent = adjacent + multi_via_grid[m_i_idx(x, y, 0, d)];

							if (z == 0 && check_fp(source_pin, Point(y, x)) < n_source_point) {
								int p_i = check_fp(source_pin, Point(y, x));
								adjacent = adjacent + source_edge[p_i];
							}
							else if (z == 0 && check_fp(dest_pin, Point(y, x)) < n_dest_point) {
								int p_i = check_fp(dest_pin, Point(y, x));
								adjacent = adjacent + dest_edge[p_i];
							}

							opt.add(adjacent == 0 || adjacent == 2);
						}
					}
				}

				// Supernodes (flow == 1)
				z3::expr adjacent = c.int_val(0);
				for (int i = 0; i < s_i; i++) {
					adjacent = adjacent + source_edge[i];
				}
				opt.add(adjacent == 1);

				adjacent = c.int_val(0);
				for (int i = 0; i < d_i; i++) {
					adjacent = adjacent + dest_edge[i];
				}
				opt.add(adjacent == 1);
			}

		}
		n_idx++;
	}

	// 4. Design rule constraints
	// 4-1. S2S for vertical metal (ver - ver)
	
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] == routing_direction::HOR) continue;
		for (int y = 0; y < track_num - 1; y++) {
			for (int x = 0; x < col_size - 1; x++) {
				z3::expr cur_ver_exist = c.bool_val(false);
				z3::expr next_ver_exist = c.bool_val(false);
				for (int n = 0; n < num_net_to_connect; n++) {
					cur_ver_exist = cur_ver_exist || ver_grid[v_idx(x, y, z, n)] == 1;
					next_ver_exist = next_ver_exist || ver_grid[v_idx(x + 1, y, z, n)] == 1;
				}
				z3::expr S2S_ver_violation = cur_ver_exist && next_ver_exist;
				opt.add(!S2S_ver_violation);
 
			}
		}
	}
	
	// 4-2. Vertical metal side-to-side (top - bottom)
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] == routing_direction::HOR) continue;
		for (int y = 0; y < track_num - 2; y++) {
			for (int x = 0; x < col_size - 1; x++) {
				z3::expr left_top_ver_exist = c.bool_val(false);
				z3::expr right_top_ver_exist = c.bool_val(false);
				z3::expr left_bot_ver_exist = c.bool_val(false);
				z3::expr right_bot_ver_exist = c.bool_val(false);
				z3::expr hor_exist = c.bool_val(false);
				for (int n = 0; n < num_net_to_connect; n++) {
					left_top_ver_exist = left_top_ver_exist || ver_grid[v_idx(x, y, z, n)] == 1;
					right_top_ver_exist = right_top_ver_exist || ver_grid[v_idx(x + 1, y, z, n)] == 1;
					left_bot_ver_exist = left_bot_ver_exist || ver_grid[v_idx(x, y + 1, z, n)] == 1;
					right_bot_ver_exist = right_bot_ver_exist || ver_grid[v_idx(x + 1, y + 1, z, n)] == 1;
					hor_exist = hor_exist || hor_grid[h_idx(x, y+1, z, n)] == 1;
				}
				z3::expr S2S_ver_violation_one = left_top_ver_exist && right_bot_ver_exist && !hor_exist;
				z3::expr S2S_ver_violation_two = left_bot_ver_exist && right_top_ver_exist && !hor_exist;
				z3::expr S2S_ver_violation = S2S_ver_violation_one || S2S_ver_violation_two;
				opt.add(!S2S_ver_violation);
 
			}
		}
	}


	// 4-3. Horizontal side-to-side for vias 
	for (int z = 0; z < layer_num - 1; z++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size - 1; x++) {
				z3::expr cur_via_exist = c.bool_val(false);
				z3::expr next_via_exist = c.bool_val(false);
				for (int n = 0; n < num_net_to_connect; n++) {
					cur_via_exist = cur_via_exist || via_grid[i_idx(x, y, z, n)] == 1;
					next_via_exist = next_via_exist || via_grid[i_idx(x + 1 , y, z, n)] == 1;
				}
				z3::expr S2S_via_violation = cur_via_exist && next_via_exist;
				opt.add(!S2S_via_violation);
			}
		}
	}

	// 4-4 Corner-to-corner for vias in PMOS/NMOS region
	for (int z = 0; z < layer_num - 1; z++) {
		for (int y = 0; y < track_num; y += 3) {
			for (int x = 0; x < col_size - 1; x++) {
				z3::expr left_top_via = c.bool_val(false);
				z3::expr right_top_via = c.bool_val(false);
				z3::expr left_bot_via = c.bool_val(false);
				z3::expr right_bot_via = c.bool_val(false);
				for (int n = 0; n < num_net_to_connect; n++) {
					left_top_via = left_top_via || via_grid[i_idx(x, y, z, n)] == 1;
					right_top_via = right_top_via || via_grid[i_idx(x + 1, y, z, n)] == 1;
					left_bot_via = left_bot_via || via_grid[i_idx(x, y + 1, z, n)] == 1;
					right_bot_via = right_bot_via || via_grid[i_idx(x + 1, y + 1, z, n)] == 1;
				}

				z3::expr C2C_via_violation_1 = left_top_via && right_bot_via;
				z3::expr C2C_via_violation_2 = right_top_via && left_bot_via;
				z3::expr C2C_via_violation = C2C_via_violation_1 || C2C_via_violation_2;
				opt.add(!C2C_via_violation);
			}
		}
	}



	// 4-5. T2S for vertical metals (ver <- hor metal) (only for 2D layers  | - )
	
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		for (int y = 0; y < track_num - 1; y++) {
			for (int x = 0; x < col_size; x++) {
				z3::expr cur_ver_exist = c.bool_val(false);
				z3::expr vio_hor_exist = c.bool_val(false);
				
				for (int n = 0; n < num_net_to_connect; n++) {
					cur_ver_exist = cur_ver_exist || ver_grid[v_idx(x, y, z, n)] == 1;

					if (x >= 2) {
						vio_hor_exist = vio_hor_exist || (hor_grid[h_idx(x - 2, y, z, n)] == 1 && hor_grid[h_idx(x - 1, y, z, n)] == 0);
						vio_hor_exist = vio_hor_exist || (hor_grid[h_idx(x - 2, y + 1, z, n)] == 1 && hor_grid[h_idx(x - 1, y + 1, z, n)] == 0);
					}
					if (x <= col_size - 3) {
						vio_hor_exist = vio_hor_exist || (hor_grid[h_idx(x + 1, y, z, n)] == 1 && hor_grid[h_idx(x, y, z, n)] == 0);
						vio_hor_exist = vio_hor_exist || (hor_grid[h_idx(x + 1, y + 1, z, n)] == 1 && hor_grid[h_idx(x, y + 1, z, n)] == 0);
					}

				}

				z3::expr T2S_violation = cur_ver_exist && vio_hor_exist;
				opt.add(!T2S_violation);
			}
		}
	}
	/*
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		for (int y = 0; y < track_num - 1; y++) {
			for (int x = 0; x < col_size - 4; x++) {
				z3::expr top_left_left = c.bool_val(false);
				z3::expr top_left_right = c.bool_val(false);
				z3::expr top_right_left = c.bool_val(false);
				z3::expr top_right_right = c.bool_val(false);

				z3::expr bot_left_left = c.bool_val(false);
				z3::expr bot_left_right = c.bool_val(false);
				z3::expr bot_right_left = c.bool_val(false);
				z3::expr bot_right_right = c.bool_val(false);
				
				z3::expr mid_ver = c.bool_val(false);

				for (int n = 0; n < num_net_to_connect; n++) {
					top_left_left = top_left_left || (hor_grid[h_idx(x, y, z, n)] == 1);
					top_left_right = top_left_right || (hor_grid[h_idx(x + 1, y, z, n)] == 1);
					top_right_left = top_right_left || (hor_grid[h_idx(x + 2, y, z, n)] == 1);
					top_right_right = top_right_right || (hor_grid[h_idx(x + 3, y, z, n)] == 1);

					bot_left_left = bot_left_left || (hor_grid[h_idx(x, y + 1, z, n)] == 1);
					bot_left_right = bot_left_right || (hor_grid[h_idx(x + 1, y + 1, z, n)] == 1);
					bot_right_left = bot_right_left || (hor_grid[h_idx(x + 2, y + 1, z, n)] == 1);
					bot_right_right = bot_right_right || (hor_grid[h_idx(x + 3, y + 1, z, n)] == 1);

					mid_ver = mid_ver || (ver_grid[v_idx(x + 2, y, z, n)] == 1);
				}

				z3::expr T2S_violation_1 = mid_ver && top_left_left && !top_left_right;
				z3::expr T2S_violation_2 = mid_ver && top_right_right && !top_right_left;
				z3::expr T2S_violation_3 = mid_ver && bot_left_left && !bot_left_right;
				z3::expr T2S_violation_4 = mid_ver && bot_right_right && !bot_right_left;
				z3::expr T2S_violation = T2S_violation_1 || T2S_violation_2 || T2S_violation_3 || T2S_violation_4;
				opt.add(!T2S_violation);
			}
		}
	}*/


	// 4-6 T2S for M1 (hor <- ver metal)
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		for (int y = 0; y < track_num - 1; y++) {
			for (int x = 0; x < col_size; x++) {
				z3::expr cur_ver_exist = c.bool_val(false);
				z3::expr top_ver_exist = c.bool_val(false);
				z3::expr top_hor_exist = c.bool_val(false);
				z3::expr bot_hor_exist = c.bool_val(false);
				z3::expr bot_ver_exist = c.bool_val(false);

				z3::expr up_hor_exist = c.bool_val(false);
				z3::expr down_hor_exist = c.bool_val(false);
				
				for (int n = 0; n < num_net_to_connect; n++) {
					cur_ver_exist = cur_ver_exist || ver_grid[v_idx(x, y, z, n)] == 1;

					if (y > 0) top_ver_exist = top_ver_exist || (ver_grid[v_idx(x, y - 1, z, n)] == 1);
					if (y < row_size - 1) bot_ver_exist = bot_ver_exist || (ver_grid[v_idx(x, y + 1, z, n)] == 1);

					if (y > 0) {
						if (x > 0) top_hor_exist = top_hor_exist || (hor_grid[h_idx(x - 1, y - 1, z, n)] == 1);
						if (x < col_size - 1) top_hor_exist = top_hor_exist || (hor_grid[h_idx(x, y - 1, z, n)] == 1);
					}
					if (y < row_size - 2) {
						if (x > 0) bot_hor_exist = bot_hor_exist || (hor_grid[h_idx(x - 1, y + 2, z, n)] == 1);
						if (x < col_size - 1) bot_hor_exist = bot_hor_exist || (hor_grid[h_idx(x, y + 2, z, n)] == 1);				
					}

					if (x > 0) up_hor_exist = up_hor_exist || (hor_grid[h_idx(x - 1, y, z, n)] == 1);
					if (x < col_size - 1) up_hor_exist = up_hor_exist || (hor_grid[h_idx(x, y, z, n)] == 1);

					if (y < row_size - 1) {
						if (x > 0) down_hor_exist = down_hor_exist || (hor_grid[h_idx(x - 1, y + 1, z, n)] == 1);
						if (x < col_size - 1) down_hor_exist = down_hor_exist || (hor_grid[h_idx(x, y + 1, z, n)] == 1);
					}

				}

				if (y != 2) {
					z3::expr T2S_violation_top = cur_ver_exist && !top_ver_exist && top_hor_exist && !up_hor_exist;
					opt.add(!T2S_violation_top);
				}
				if (y != 1) {
					z3::expr T2S_violation_bot = cur_ver_exist && !bot_ver_exist && bot_hor_exist && !down_hor_exist;
					opt.add(!T2S_violation_bot);
				}
			}
		}
	}


	// 4-7. M1 MAR Rule (avoid M1 island)
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				z3::expr cur_pt_metal_exist = (metal_grid[idx(x, y, 0, n)] == 1);

				z3::expr metal_exist = c.bool_val(false);
				if (x > 0) metal_exist = metal_exist || hor_grid[h_idx(x - 1, y, 0, n)] == 1;
				if (x < col_size - 1) metal_exist = metal_exist || hor_grid[h_idx(x, y, 0, n)] == 1;

				if (y > 0) metal_exist = metal_exist || ver_grid[v_idx(x, y - 1, 0, n)] == 1;
				if (y < track_num - 1) metal_exist = metal_exist || ver_grid[v_idx(x, y, 0, n)] == 1;

				z3::expr double_via_violation = cur_pt_metal_exist && !metal_exist;
				opt.add(!double_via_violation);

			}
		}
	}

	// 4-8. Horizontal End-to-End Spacing (-  -)
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] == routing_direction::VER) continue;
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size - 3; x++) {
				z3::expr cur_hor_exist = c.bool_val(false);
				z3::expr next_hor_exist = c.bool_val(false);
				z3::expr two_next_hor_exist = c.bool_val(false);
				/*
				z3::expr three_next_hor_exist = c.bool_val(false);

				z3::expr left_ver_exist = c.bool_val(false);
				z3::expr right_ver_exist = c.bool_val(false);
				*/
				for (int n = 0; n < num_net_to_connect; n++) {
					cur_hor_exist = cur_hor_exist || (hor_grid[h_idx(x, y, z, n)] == 1);
					next_hor_exist = next_hor_exist || (hor_grid[h_idx(x + 1, y, z, n)] == 1);
					two_next_hor_exist = two_next_hor_exist || (hor_grid[h_idx(x + 2, y, z, n)] == 1);
					
					/*
					if (y > 0) left_ver_exist = left_ver_exist || (ver_grid[v_idx(x + 1, y - 1, z, n)] == 1);
					if (y < track_num - 1) left_ver_exist = left_ver_exist || (ver_grid[v_idx(x + 1, y, z, n)] == 1);
					
					if (x < col_size - 4) {
						three_next_hor_exist = three_next_hor_exist || hor_grid[h_idx(x + 3, y, z, n)] == 1;
						if (y > 0) right_ver_exist = right_ver_exist || (ver_grid[v_idx(x + 3, y - 1, z, n)] == 1);
						if (y < track_num - 1) right_ver_exist = right_ver_exist || (ver_grid[v_idx(x + 3, y, z, n)] == 1);

					}
					*/
				}
				z3::expr E2E_violation_one = cur_hor_exist && !next_hor_exist && two_next_hor_exist;
				/*
				z3::expr E2E_violation_two = cur_hor_exist && !next_hor_exist && !two_next_hor_exist && three_next_hor_exist && !left_ver_exist && !right_ver_exist;
				z3::expr E2E_violation = E2E_violation_one || E2E_violation_two;
				opt.add(!E2E_violation);
				*/
				opt.add(!E2E_violation_one);
			}
		}
	}

	// 4-9. Avoid T2S with M1 Power Metal
	/*
	if (metal_dir[0] != routing_direction::HOR) {
		// VDD rail
		for (int x = 0; x < col_size; x++) {
			z3::expr ver_exist = c.bool_val(false);
			z3::expr hor_exist = c.bool_val(false);
			for (int n = 0; n < num_net_to_connect; n++) {
				ver_exist = ver_exist || (ver_grid[v_idx(x, 0, 0, n)] == 1);
				if (x - 1 >= 0) hor_exist = hor_exist || (hor_grid[h_idx(x - 1, 0, 0, n)] == 1);
				if (x<= col_size - 2) hor_exist = hor_exist || (hor_grid[h_idx(x, 0, 0, n)] == 1); 
			}
			z3::expr vdd_vio = ver_exist && !hor_exist;
			opt.add(!vdd_vio);
		}
		// GND rail
		for (int x = 0; x < col_size; x++) {
			z3::expr ver_exist = c.bool_val(false);
			z3::expr hor_exist = c.bool_val(false);
			for (int n = 0; n < num_net_to_connect; n++) {
				ver_exist = ver_exist || (ver_grid[v_idx(x, 3, 0, n)] == 1);
				if (x - 1 >= 0) hor_exist = hor_exist || (hor_grid[h_idx(x - 1, 4, 0, n)] == 1);
				if (x <= col_size - 2) hor_exist = hor_exist || (hor_grid[h_idx(x, 4, 0, n)] == 1); 
			}
			z3::expr vdd_vio = ver_exist && !hor_exist;
			opt.add(!vdd_vio);
		}
	}*/

	// 4-10. Metal horizontal Corner-to-corner in PMOS/NMOS Region
	/*
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] == routing_direction::VER) continue;
		for (int y = 0; y < track_num; y += 3) {
			for (int x = 0; x < col_size - 3; x++) {
				z3::expr top_left_hor = c.bool_val(false);
				z3::expr top_mid_hor = c.bool_val(false);
				z3::expr top_right_hor = c.bool_val(false);
				z3::expr bot_left_hor = c.bool_val(false);
				z3::expr bot_mid_hor = c.bool_val(false);
				z3::expr bot_right_hor = c.bool_val(false);
				z3::expr left_ver = c.bool_val(false);
				z3::expr right_ver = c.bool_val(false);
				for (int n = 0; n < num_net_to_connect; n++) {
					top_left_hor = top_left_hor || hor_grid[h_idx(x, y, z, n)] == 1;
					top_mid_hor = top_mid_hor || hor_grid[h_idx(x + 1, y, z, n)] == 1;
					top_right_hor = top_right_hor || hor_grid[h_idx(x + 2, y, z, n)] == 1;
					bot_left_hor = bot_left_hor || hor_grid[h_idx(x, y + 1, z, n)] == 1;
					bot_mid_hor = bot_mid_hor || hor_grid[h_idx(x + 1, y + 1, z, n)] == 1;
					bot_right_hor = bot_right_hor || hor_grid[h_idx(x + 2, y + 1, z, n)] == 1;
					left_ver = left_ver || ver_grid[v_idx(x + 1, y, z, n)] == 1;
					right_ver = right_ver || ver_grid[v_idx(x + 2, y, z, n)] == 1;
				
				}
				z3::expr C2C_hor_violation_1 = top_left_hor && bot_right_hor && !top_mid_hor && !bot_mid_hor && !left_ver && !right_ver;
				z3::expr C2C_hor_violation_2 = top_right_hor && bot_left_hor && !top_mid_hor && !bot_mid_hor && !left_ver && !right_ver;
				z3::expr C2C_hor_violation = C2C_hor_violation_1 || C2C_hor_violation_2;
				opt.add(!C2C_hor_violation);
			}
		}
	}
	*/

	// 4-11. M1 vertical tip to horizontal side spacing
	/*
	// Upside
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		int y = 0;
		for (int x = 0; x < col_size - 2; x++) {
			z3::expr top_left_hor = c.bool_val(false);
			z3::expr top_right_hor = c.bool_val(false);
			z3::expr mid_left_hor = c.bool_val(false);
			z3::expr mid_right_hor = c.bool_val(false);
			z3::expr top_left_ver = c.bool_val(false);
			z3::expr top_mid_ver = c.bool_val(false);
			z3::expr top_right_ver = c.bool_val(false);
			z3::expr bot_left_ver = c.bool_val(false);
			z3::expr bot_right_ver = c.bool_val(false);
			for (int n = 0; n < num_net_to_connect; n++) {
				top_left_hor = top_left_hor || hor_grid[h_idx(x, y, z, n)] == 1;
				top_right_hor = top_right_hor || hor_grid[h_idx(x + 1, y, z, n)] == 1;
				mid_left_hor = mid_left_hor || hor_grid[h_idx(x, y + 1, z, n)] == 1;
				mid_right_hor = mid_right_hor || hor_grid[h_idx(x + 1, y + 1, z, n)] == 1;
				top_left_ver = top_left_ver || ver_grid[v_idx(x, y, z, n)] == 1;
				top_mid_ver = top_mid_ver || ver_grid[v_idx(x + 1, y, z, n)] == 1;
				top_right_ver = top_right_ver || ver_grid[v_idx(x + 2, y, z, n)] == 1;
				bot_left_ver = bot_left_ver || ver_grid[v_idx(x, y + 1, z, n)] == 1;
				bot_right_ver = bot_right_ver || ver_grid[v_idx(x + 2, y + 1, z, n)] == 1;
			}
			z3::expr c2c_vio_1 = bot_left_ver && top_right_hor && !top_left_hor && !mid_left_hor && !top_left_ver && !top_mid_ver;
			z3::expr c2c_vio_2 = bot_right_ver && top_left_hor && !top_right_hor && !top_mid_ver && !top_right_ver && !mid_right_hor;
			z3::expr c2c_vio = c2c_vio_1 || c2c_vio_2;
			opt.add(!c2c_vio);
		}
	}
	// Downside
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		int y = 2;
		for (int x = 0; x < col_size - 2; x++) {
			z3::expr mid_left_hor = c.bool_val(false);
			z3::expr mid_right_hor = c.bool_val(false);
			z3::expr bot_left_hor = c.bool_val(false);
			z3::expr bot_right_hor = c.bool_val(false);
			z3::expr top_left_ver = c.bool_val(false);
			z3::expr top_right_ver = c.bool_val(false);
			z3::expr bot_left_ver = c.bool_val(false);
			z3::expr bot_mid_ver = c.bool_val(false);
			z3::expr bot_right_ver = c.bool_val(false);
			for (int n = 0; n < num_net_to_connect; n++) {
				mid_left_hor = mid_left_hor || hor_grid[h_idx(x, y + 1, z, n)] == 1;
				mid_right_hor = mid_right_hor || hor_grid[h_idx(x + 1, y + 1, z, n)] == 1;
				bot_left_hor = bot_left_hor || hor_grid[h_idx(x, y + 2, z, n)] == 1;
				bot_right_hor = bot_right_hor || hor_grid[h_idx(x + 1, y + 2, z, n)] == 1;
				top_left_ver = top_left_ver || ver_grid[v_idx(x, y, z, n)] == 1;
				top_right_ver = top_right_ver || ver_grid[v_idx(x + 2, y, z, n)] == 1;
				bot_left_ver = bot_left_ver || ver_grid[v_idx(x, y + 1, z, n)] == 1;
				bot_mid_ver = bot_mid_ver || ver_grid[v_idx(x + 1, y + 1, z, n)] == 1;
				bot_right_ver = bot_right_ver || ver_grid[v_idx(x + 2, y + 1, z, n)] == 1;
			}
			z3::expr c2c_vio_1 = top_left_ver && bot_right_hor && !mid_left_hor && !bot_left_hor && !bot_left_ver && !bot_mid_ver;
			z3::expr c2c_vio_2 = top_right_ver && bot_left_hor && !mid_right_hor && !bot_right_hor && !bot_mid_ver && !bot_right_ver;
			z3::expr c2c_vio = c2c_vio_1 || c2c_vio_2;
			opt.add(!c2c_vio);
		}
	}
	*/


	// 4-6. Avoid via turning
	/*
	for (int z = 0; z < layer_num; z++) {
		if (metal_dir[z] != routing_direction::BOTH) continue;
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				z3::expr up_exist = c.bool_val(false);
				z3::expr down_exist = c.bool_val(false);
				z3::expr left_exist = c.bool_val(false);
				z3::expr right_exist = c.bool_val(false);
				z3::expr via_exist = c.bool_val(false);

				for (int n = 0; n < num_net_to_connect; n++) {
					if (x > 0) left_exist = left_exist || (hor_grid[h_idx(x - 1, y, z, n)] == 1);
					if (x < col_size - 1) right_exist = right_exist || (hor_grid[h_idx(x, y, z, n)] == 1);
					if (y > 0) up_exist = up_exist || (ver_grid[v_idx(x, y - 1, z, n)] == 1);
					if (y < track_num - 1) down_exist = down_exist || (ver_grid[v_idx(x, y, z, n)] == 1);
				
					via_exist = via_exist || (via_grid[i_idx(x, y, z, n)] == 1);
				}

				z3::expr ver_one = (up_exist && !down_exist) || (!up_exist && down_exist);
				z3::expr hor_one = (left_exist && !right_exist) || (!left_exist && right_exist);
 
				z3::expr via_turn = via_exist && ver_one && hor_one;
				opt.add(!via_turn);
			}
		}
	}*/


	// 5. I/O pin extraction
	
	for (auto& IO_pin : IO_floating_pins) {
		std::string pin_name = IO_pin.first;
		auto& fp_list = IO_pin.second;
		if (fp_list.size() != 1) {
			std::cout << "IO error!" << " Pin_name: " << pin_name << ", fp_list: " << fp_list.size() << std::endl;
			exit(0);
		}

		z3::expr_vector IO_candidates(c);
		int f_i = 0;
		for (auto fpoint : fp_list[0]) {
			std::string point_name = pin_name + "_point_(" + std::to_string(fpoint.x) + ", " + std::to_string(fpoint.y) + ")";
			IO_candidates.push_back(c.int_const(point_name.c_str()));
			opt.add(IO_candidates[f_i] >= 0 && IO_candidates[f_i] <= 1);
			f_i++;
		}

		// Extract only one point
		z3::expr IO_num = c.int_val(0);
		for (int i = 0; i < f_i; i++) {
			IO_num = IO_num + IO_candidates[i];
		}
		opt.add(IO_num == 1);
		
		// Do not overlap with routing metals
		// Spacing violation with routing metals

		f_i = 0;
		for (auto fpoint : fp_list[0]) {
			z3::expr left_top_ver_exist = c.bool_val(false);
			z3::expr left_bot_ver_exist = c.bool_val(false);
			z3::expr right_top_ver_exist = c.bool_val(false);
			z3::expr right_bot_ver_exist = c.bool_val(false);

			z3::expr hor_exist = c.bool_val(false);

			z3::expr is_metal = c.bool_val(false);
			for (int n = 0; n < num_net_to_connect; n++) {
				if (fpoint.x > 0) {
					if (fpoint.y > 0) left_top_ver_exist = left_top_ver_exist || ver_grid[v_idx(fpoint.x - 1, fpoint.y - 1, 0, n)] == 1;
					if (fpoint.y < track_num - 1) left_bot_ver_exist = left_bot_ver_exist || ver_grid[v_idx(fpoint.x - 1, fpoint.y, 0, n)] == 1;
				}
				if (fpoint.x < col_size - 1) {
					if (fpoint.y > 0) right_top_ver_exist = right_top_ver_exist || ver_grid[v_idx(fpoint.x + 1, fpoint.y - 1, 0, n)] == 1;
					if (fpoint.y < track_num - 1) right_bot_ver_exist = right_bot_ver_exist || ver_grid[v_idx(fpoint.x + 1, fpoint.y, 0, n)] == 1;
				}
				is_metal = is_metal || metal_grid[idx(fpoint.x, fpoint.y, 0, n)] == 1;

				if (fpoint.x > 1) hor_exist = hor_exist || (hor_grid[h_idx(fpoint.x - 2, fpoint.y, 0, n)] == 1);
				if (fpoint.x < col_size - 1) hor_exist = hor_exist || (hor_grid[h_idx(fpoint.x + 1, fpoint.y, 0, n)] == 1);

			}
			z3::expr ver_exist = left_top_ver_exist || left_bot_ver_exist || right_top_ver_exist || right_bot_ver_exist;
			
			opt.add(z3::implies(IO_candidates[f_i] == 1, !ver_exist && !is_metal && !hor_exist));
			
			f_i++;

		}
	}
	
	// M2 restriction
/*
	z3::expr sum_m2 = c.int_val(0);
	
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size - 1; x++) {
				if (metal_dir[1] != routing_direction::VER) sum_m2 = sum_m2 + hor_grid[h_idx(x, y, 1, n)];
			}
		}
	}
	int num_resources = track_num * (col_size - 1);
	int limit = num_resources / 2;
	opt.add(sum_m2 <= limit);	
*/

	// Objective
	
	z3::expr sum_m1 = c.int_val(0);
	z3::expr sum_m2 = c.int_val(0);
	//z3::expr sum_v1 = c.int_val(0);

	
	// Hor metal (M1, M2)
	
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size - 1; x++) {
				if (metal_dir[0] != routing_direction::VER) sum_m1 = sum_m1 + hor_grid[h_idx(x, y, 0, n)];
				if (metal_dir[1] != routing_direction::VER) sum_m2 = sum_m2 + hor_grid[h_idx(x, y, 1, n)];
			}
		}
	}

	
	// Ver metal (M1)
	
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int y = 0; y < track_num - 1; y++) {
			for (int x = 0; x < col_size; x++) {
				if (metal_dir[0] != routing_direction::HOR) sum_m1 = sum_m1 + ver_grid[v_idx(x, y, 0, n)];
			}
		}
	}

	// Via (v1)
	/*
	for (int n = 0; n < num_net_to_connect; n++) {
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				sum_v1 = sum_v1 + via_grid[i_idx(x, y, 0, n)];
			}
		} 
	}*/
	
		

	//z3::optimize::handle obj1 = opt.minimize(m2_track);
	if (setting.min_m2) z3::optimize::handle obj1 = opt.minimize(sum_m2);
	//z3::optimize::handle obj2 = opt.minimize(sum_v1);
	//z3::optimize::handle obj1 = opt.minimize(sum_m2);
	if (setting.min_m1) z3::optimize::handle obj2 = opt.minimize(sum_m1);
	
}


z3::check_result Router::solve_SMT (z3::optimize &opt) {
	std::cout << opt << std::endl;
	z3::check_result result = opt.check();
	std::cout << opt.statistics() << std::endl;
	std::cout << result << std::endl;
	if (result == z3::sat) {
		z3::model m = opt.get_model();
		std::cout << m << std::endl;
	}
	return result;
}

void Router::gather_result(z3::context &c, z3::optimize &opt) {
	z3::model m = opt.get_model();

	// Variables for detailed routing
	// metal routing map (x, y, z, n)
	z3::expr_vector metal_grid(c);

	z3::expr_vector hor_grid(c);
	z3::expr_vector ver_grid(c);
	z3::expr_vector via_grid(c);

	int track_num = row_size;
	int num_net_to_connect = 0;
	int layer_num = num_layer;


	auto idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * track_num * col_size + z * track_num * col_size + y * col_size + x;
	};

	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string metal_name = iter.first + "_(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					
					metal_grid.push_back(c.int_const(metal_name.c_str()));
				}
			}
		}
		num_net_to_connect++;
	}	

	// hor_grid
	auto h_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * track_num * (col_size - 1) + z * track_num * (col_size - 1) + y * (col_size - 1) + x;
	};
	int n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size - 1; x++) {
					std::string hor_name = iter.first + "_h(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					hor_grid.push_back(c.int_const(hor_name.c_str()));
				}
			}
		}		
		n++;
	}

	// ver_grid
	auto v_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * layer_num * (track_num - 1) * col_size + z * (track_num - 1) * col_size + y * col_size + x;
	};
	n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num; z++) {
			for (int y = 0; y < track_num - 1; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string ver_name = iter.first + "_v(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					ver_grid.push_back(c.int_const(ver_name.c_str()));
				}
			}
		}		
		n++;
	}

	// via_grid
	auto i_idx = [&](int x, int y, int z, int n_idx) {
		return n_idx * (layer_num - 1) * track_num * col_size + z * track_num * col_size + y * col_size + x;
	};
	n = 0;
	for (auto & iter : pin_map) {
		for (int z = 0; z < layer_num - 1; z++) {
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					std::string via_name = iter.first + "_i(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
					via_grid.push_back(c.int_const(via_name.c_str()));

				}
			}
		}		
		n++;
	}
	routing_result["overall"] = std::make_shared<RoutingResult>(num_layer, row_size, col_size, false);
		
	int n_idx = 0;
	for (auto & iter : pin_map) {
		std::string net_name = iter.first;

		routing_result[net_name] = std::make_shared<RoutingResult>(num_layer, row_size, col_size, false);

		// Parse V0 result
		auto& fp_list = floating_pins[iter.first];
		int n_pin = fp_list.size();

		for (int d = 0; d < n_pin - 1; d++) {
			auto& source_pin = fp_list[0];
			auto& dest_pin = fp_list[d + 1];

			for (auto source_point : source_pin) {
				std::string source_name = iter.first + "_source_" + std::to_string(d) + "_(" + std::to_string(source_point.x) + ", " + std::to_string(source_point.y) + ")";
				//std::cout << source_name << std::endl;
				z3::expr source_point_exp = c.int_const(source_name.c_str());
				
				if (m.eval(source_point_exp).get_numeral_int() == 1) {
					routing_result[net_name]->via_grid[0][source_point.y][source_point.x] = 1;
					routing_result["overall"]->via_grid[0][source_point.y][source_point.x] = 1;
				}
			}

			for (auto dest_point : dest_pin) {
				std::string dest_name = iter.first + "_dest_" + std::to_string(d) + "_(" + std::to_string(dest_point.x) + ", " + std::to_string(dest_point.y) + ")";
				//std::cout << dest_name << std::endl;
				z3::expr dest_pin_exp = c.int_const(dest_name.c_str());

				if (m.eval(dest_pin_exp).get_numeral_int() == 1) {
					routing_result[net_name]->via_grid[0][dest_point.y][dest_point.x] = 1;
					routing_result["overall"]->via_grid[0][dest_point.y][dest_point.x] = 1;
				}
			}
		}


		// M1_Vertex
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				int index = idx(x, y, 0, n_idx);
				if (m.eval(metal_grid[index]).get_numeral_int() == 1) {
					routing_result[net_name]->metal_grid[0][y][x] = 1;
					routing_result["overall"]->metal_grid[0][y][x] = 1;
				}

				if (x < col_size - 1) {
					if (m.eval(hor_grid[h_idx(x, y, 0, n_idx)]).get_numeral_int() == 1) {
						routing_result[net_name]->hor_grid[0][y][x] = 1;
						routing_result["overall"]->hor_grid[0][y][x] = 1;
					} 
				}
			}
			if (y == track_num - 1) continue;
			for (int x = 0; x < col_size; x++) {
				if (m.eval(ver_grid[v_idx(x, y, 0, n_idx)]).get_numeral_int() == 1) {
					routing_result[net_name]->ver_grid[0][y][x] = 1;
					routing_result["overall"]->ver_grid[0][y][x] = 1;					
				}
			}
		}

		// V1
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				int index = i_idx(x, y, 0, n_idx);
				if (m.eval(via_grid[index]).get_numeral_int() == 1) {
					routing_result[net_name]->via_grid[1][y][x] = 1;
					routing_result["overall"]->via_grid[1][y][x] = 1;
				}
			}
		}


		// M2
		for (int y = 0; y < track_num; y++) {
			for (int x = 0; x < col_size; x++) {
				int index = idx(x, y, 1, n_idx);
				if (m.eval(metal_grid[index]).get_numeral_int() == 1) {
					routing_result[net_name]->metal_grid[1][y][x] = 1;
					routing_result["overall"]->metal_grid[1][y][x] = 1;
				} 
				if (x < col_size - 1) {
					if (m.eval(hor_grid[h_idx(x, y, 1, n_idx)]).get_numeral_int() == 1) {
						routing_result[net_name]->hor_grid[1][y][x] = 1;
						routing_result["overall"]->hor_grid[1][y][x] = 1;
					}
				}
			}			
			if (y == track_num - 1) continue;
			for (int x = 0; x < col_size; x++) {
				if (m.eval(ver_grid[v_idx(x, y, 1, n_idx)]).get_numeral_int() == 1) {
					routing_result[net_name]->ver_grid[1][y][x] = 1;
					routing_result["overall"]->ver_grid[1][y][x] = 1;					
				}
			}
		}

		if (layer_num > 2) {
			// V2
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					int index = i_idx(x, y, 1, n_idx);
					if (m.eval(via_grid[index]).get_numeral_int() == 1) {
						routing_result[net_name]->via_grid[2][y][x] = 1;
						routing_result["overall"]->via_grid[2][y][x] = 1;
					} 
				}
			}


			// M3
			for (int y = 0; y < track_num; y++) {
				for (int x = 0; x < col_size; x++) {
					int index = idx(x, y, 2, n_idx);
					if (m.eval(metal_grid[index]).get_numeral_int() == 1) {
						routing_result[net_name]->metal_grid[2][y][x] = 1;
						routing_result["overall"]->metal_grid[2][y][x] = 1;
					}
					if (x < col_size - 1) {
						if (m.eval(hor_grid[h_idx(x, y, 2, n_idx)]).get_numeral_int() == 1) {
							routing_result[net_name]->hor_grid[2][y][x] = 1;
							routing_result["overall"]->hor_grid[2][y][x] = 1;
						}
					}
				}			
				if (y == track_num - 1) continue;
				for (int x = 0; x < col_size; x++) {
					if (m.eval(ver_grid[v_idx(x, y, 2, n_idx)]).get_numeral_int() == 1) {
						routing_result[net_name]->ver_grid[2][y][x] = 1;
						routing_result["overall"]->ver_grid[2][y][x] = 1;					
					} 
				} 
			}
		}

		n_idx++;
	}

	// Print IO_pins
	for (auto& IO_pin : IO_floating_pins) {
		std::string pin_name = IO_pin.first;

		routing_result[pin_name] = std::make_shared<RoutingResult>(num_layer, row_size, col_size, true);

		auto& fp_list = IO_pin.second;
		if (fp_list.size() != 1) {
			std::cout << "IO error!" << std::endl;
			exit(0);
		}
		
		for (auto source_point : fp_list[0]) {
			std::string source_name = pin_name + "_point_(" + std::to_string(source_point.x) + ", " + std::to_string(source_point.y) + ")";
			//std::cout << source_name << std::endl;
			z3::expr source_point_exp = c.int_const(source_name.c_str());
			
			if (m.eval(source_point_exp).get_numeral_int() == 1) {
				routing_result["overall"]->metal_grid[0][source_point.y][source_point.x] = 1;
				routing_result["overall"]->via_grid[0][source_point.y][source_point.x] = 1;
				routing_result[pin_name]->metal_grid[0][source_point.y][source_point.x] = 1;
				routing_result[pin_name]->via_grid[0][source_point.y][source_point.x] = 1;
			

			} 
		}
	}
}

void Router::print_result(std::ofstream &out) {

	// Routing result for individual pins
	out << "-------- Routing Results -----------------" << std::endl;
	for (auto& pin_route : routing_result) {
		std::string name = pin_route.first;
		auto pin_route_result = pin_route.second;

		if (name == "overall") continue;
		
		out << "========== " << name << " ===========" << std::endl;

		// V0
		out << "V0" << std::endl;
		for (int y = 0; y < row_size; y++) {
			for (int x = 0; x < col_size; x++) {
				out << pin_route_result->via_grid[0][y][x] << " ";

			}
			out << std::endl << std::endl;
		}
		out << std::endl;		

		// M1
		out << "M1" << std::endl;
		for (int y = 0; y < row_size; y++) {
			for (int x = 0; x < col_size; x++) {
				out << pin_route_result->metal_grid[0][y][x];

				if (x < col_size - 1) {
					if (pin_route_result->hor_grid[0][y][x] == 1) out << "-";
					else out << " ";
				}
			}
			out << std::endl;
			if (y == row_size - 1) continue;
			for (int x = 0; x < col_size; x++) {
				if (pin_route_result->ver_grid[0][y][x] == 1) out << "| ";
				else out << "  ";
			}
			out << std::endl;
		}
		out << std::endl;		

		// V1
		out << "V1" << std::endl;
		for (int y = 0; y < row_size; y++) {
			for (int x = 0; x < col_size; x++) {
				out << pin_route_result->via_grid[1][y][x] << " ";
			}
			out << std::endl << std::endl;
		}
		out << std::endl;		

		// M2
		out << "M2" << std::endl;
		for (int y = 0; y < row_size; y++) {
			for (int x = 0; x < col_size; x++) {
				out << pin_route_result->metal_grid[1][y][x];

				if (x < col_size - 1) {
					if (pin_route_result->hor_grid[1][y][x] == 1) out << "-";
					else out << " ";
				}
			}
			out << std::endl;
			if (y == row_size - 1) continue;
			for (int x = 0; x < col_size; x++) {
				if (pin_route_result->ver_grid[1][y][x] == 1) out << "| ";
				else out << "  ";
			}
			out << std::endl;
		}
		out << std::endl;		
	}

	// Overall
	out << "--------------- Overall -----------------" << std::endl;
	auto overall_result = routing_result["overall"];
	// V0
	out << "V0" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < col_size; x++) {
			out << overall_result->via_grid[0][y][x] << " ";
		}
		out << std::endl << std::endl;
	}
	out << std::endl;		

	// M1
	out << "M1" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < col_size; x++) {
			out << overall_result->metal_grid[0][y][x];
			if (x < col_size - 1) {
				if (overall_result->hor_grid[0][y][x] == 1) out << "-";
				else out << " ";
			}
		}
		out << std::endl;
		if (y == row_size - 1) continue;
		for (int x = 0; x < col_size; x++) {
			if (overall_result->ver_grid[0][y][x] == 1) out << "| ";
			else out << "  ";
		}
		out << std::endl;
	}
	out << std::endl;		

	// V1
	out << "V1" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < col_size; x++) {
			out << overall_result->via_grid[1][y][x] << " ";
		}
		out << std::endl << std::endl;
	}
	out << std::endl;		
	
	int m2_hor_resource = (col_size - 1) * row_size;
	int m2_hor_usage = 0;

	// M2
	out << "M2" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < col_size; x++) {
			out << overall_result->metal_grid[1][y][x];

			if (x < col_size - 1) {
				if (overall_result->hor_grid[1][y][x] == 1) {
					m2_hor_usage++;
					out << "-";
				} 
				else out << " ";
			}
		}
		out << std::endl;
		if (y == row_size - 1) continue;
		for (int x = 0; x < col_size; x++) {
			if (overall_result->ver_grid[1][y][x] == 1) out << "| ";
			else out << "  ";
		}
		out << std::endl;
	}
	out << std::endl;		

	m2_usage = static_cast<double>(m2_hor_usage) / m2_hor_resource;


}

bool Router::routing(fs::path output_path) {

	if(place_sol.cellWidth == 0) return false;
	
	initialize_grid();
	generate_pin_map();

	z3::set_param("timeout", 60 * 60000);
	//z3::set_param("parallel.enable", true);
	//z3::set_param("parallel.threads.max", 4);
	//std::cout << opt << std::endl;

	//std::string filePath = "./result_mega/" + cell.name + "_" + std::to_string(index) + ".txt";
	//std::ofstream out(filePath);

	std::ofstream out(output_path.string());

	std::cout << output_path << std::endl;

	// Print placement solution
	for (int i = 0; i < place_sol.cellWidth; i++) {
        out << "[Column " << i + 1 << "]" << std::endl;
        out << "NMOS : " << place_sol.nmos[i].name << "(" << place_sol.nmos[i].nfin << ") [" << place_sol.nmos[i].left << " " << place_sol.nmos[i].gate << " " << place_sol.nmos[i].right << "], ";
        out << "PMOS : " << place_sol.pmos[i].name << "(" << place_sol.pmos[i].nfin << ") [" << place_sol.pmos[i].left << " " << place_sol.pmos[i].gate << " " << place_sol.pmos[i].right << "]" << std::endl;
    }
	out << std::endl;

	// Print h_net_density, v_net_density
	out.setf(std::ios::fixed);
	out.precision(2);
	out << "H Net Density" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < 2 * place_sol.cellWidth + 1; x++) {
			out << place_sol.h_net_den[y][x] << " ";
		}
		out << std::endl;
	}
	out << std::endl;
	for (int x = 0; x < 2 * place_sol.cellWidth + 1; x++) out << place_sol.hor_cong[x] << " ";
	out << std::endl << std::endl;
	
	out << "V Net Density" << std::endl;
	for (int y = 0; y < row_size; y++) {
		for (int x = 0; x < 2 * place_sol.cellWidth + 1; x++) {
			out << place_sol.v_net_den[y][x] << " ";
		}
		out << std::endl;
	}
	out << std::endl;
	for (int x = 0; x < 2 * place_sol.cellWidth + 1; x++) out << place_sol.ver_cong[x] << " ";
	out << std::endl << std::endl;

	out << "Cost = " << place_sol.cost << std::endl;
	out.unsetf(std::ios::fixed);
	
    out << "[NOR_HPWL=" << place_sol.nor_hpwl << ", MAX_H_GRID=" << place_sol.max_h_grid << ", MAX_V_GRID=" << place_sol.max_v_grid << ", MAX_H_COLUMN=" << place_sol.max_h_column << ", MAX_V_COLUMN=" << place_sol.max_v_column << ", MAX_H_ROW=" << place_sol.max_h_row << ", MAX_V_ROW=" << place_sol.max_v_row << std::endl << std::endl;	
	
	// Print Floating pins
	out << "---------------- Pin List -------------------" << std::endl;
	for (auto& iter : pin_map) {
		out << "Net " << iter.first << std::endl;
		for (int i = 0; i < row_size; i++) {
			for (int j = 0; j < col_size; j++) {
				out << iter.second[i][j] << " ";
			}
			out << std::endl;
		}
		out << std::endl;
		
		auto& floating_points = floating_pins[iter.first];
		for (auto& fp_list : floating_points) {
			for (auto& fp : fp_list) {
				out << "(" << fp.y << ", " << fp.x << ") ";
			}
			out << std::endl;
		}
		out << std::endl;
	}	
	
	z3::context c;
	z3::optimize opt(c);

	add_detailed_routing_formulation(c, opt);

	auto start = std::chrono::high_resolution_clock::now();
	auto result = opt.check();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	runtime = duration.count();
	//out << "Routing time : " << duration.count() << "ms" << std::endl;
	
	if (result == z3::sat) {
		gather_result (c, opt);
		print_result (out);
		int var_num = 0;
		int clause_num = 0;
		auto st = opt.statistics();
		for (int j = 0; j < st.size(); j++) {
			std::string k = st.key(j);
			if (k == "sat mk var") var_num = st.uint_value(j);
			if (k == "sat mk clause 2ary") clause_num += st.uint_value(j);
			if (k == "sat mk clause 3ary") clause_num += st.uint_value(j);
			if (k == "sat mk clause nary") clause_num += st.uint_value(j);
		}
		out << "var_num : " << var_num << ", clause_num : " << clause_num << std::endl;
		out << "Routing time : " << duration.count() << "ms" << std::endl;

		is_routable = true;

		std::cout << "SAT!" << std::endl;
		
		if (setting.gen_gds) {
			auto ascii_path = output_path.replace_extension(fs::path(".ascii"));
			auto cell_name = output_path.stem();
			std::ofstream ascii_out(ascii_path.string());
			generate_ascii(ascii_out, cell_name.string());
			ascii_to_gdsii(ascii_path);
		}

	}

	else { 
		std::cout << "UNSAT!" << std::endl;

		out << "Unsat!" << std::endl;
		out << "Routing time : " << duration.count() << "ms" << std::endl;

		is_routable = false;
	}
	out.close();
	std::cout << "routing step done!" << std::endl;
    return true;
}


void Router::generate_ascii(std::ofstream &out, std::string cell_name) {

	auto draw_boundary = [](std::ofstream &d_out, int layer_num, std::vector<Point> &points) {
		int n_point = points.size();

		d_out << "BOUNDARY;" << std::endl;
		d_out << "LAYER " << layer_num << ";" << std::endl;
		d_out << "DATATYPE 0;" << std::endl;
		d_out << "XY " << n_point << ";" << std::endl;
		for (int i = 0; i < n_point; i++) {
			d_out << " X: " << points[i].x * 4 << ";		 Y: " << points[i].y * 4 << ";" << std::endl;
		}
		d_out << "ENDEL;" << std::endl << std::endl;
	};


	// Print prefix
	out << "HEADER 5;" << std::endl;
	out << "BGNLIB;" << std::endl;
	out << " LASTMOD  {5-17-2016:1:5};" << std::endl;
	out << " LASTACC  {5-17-2016:1:5};" << std::endl;
	out << "LIBNAME ASAP7;" << std::endl;
	out << "UNITS;" << std::endl;
	out << " USERUNITS 2.500000e-04;" << std::endl;
	out << " PHYSUNITS 2.500000e-10;" << std::endl;
	out << std::endl;
	out << "BGNSTR;" << std::endl;
	out << " CREATION {5-17-2016:1:5};" << std::endl;
	out << " LASTMOD  {5-17-2016:1:5};" << std::endl;
	out << "STRNAME " << cell_name << ";" << std::endl;
	out << std::endl;


	// Draw WELL
	int gate_pitch = static_cast<int>(ASAP_DR::GATE_PITCH);
	int num_gate = place_sol.nmos.size();
	int x_right_boundary = gate_pitch * (num_gate + 2);

	int cell_height = static_cast<int>(ASAP_DR::CELL_HEIGHT);

	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::WELL) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 2 << ";" << std::endl;
	out << "ENDEL;" << std::endl;

	// Label WELL
	out << "TEXT;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::WELL) << ";" << std::endl;
	out << "TEXTTYPE 251;" << std::endl;
	out << "PRESENTATION 0,1,1;" << std::endl;
	out << "PATHTYPE 0;" << std::endl;
	out << "STRANS 0,0,0;" << std::endl;
	out << "MAG 2.500000e-02;" << std::endl;
	out << "XY 1;" << std::endl;
	out << " X: " << x_right_boundary * 2 << 	";		 Y: " << cell_height * 3 << ";" << std::endl;
	out << "STRING VDD;" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Draw NSELECT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::NSELECT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: 0;" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: 0;" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: 0;		 Y: 0;" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Draw PSELECT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::PSELECT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 2 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 2 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Draw BOUNDARY
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::BOUNDARY) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: 0;" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: 0;" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << cell_height * 4 << ";" << std::endl;
	out << " X: 0;		 Y: 0;" << std::endl;
	out << "ENDEL;" << std::endl;

	// Label P_SUB
	out << "TEXT;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::P_SUB) << ";" << std::endl;
	out << "TEXTTYPE 251;" << std::endl;
	out << "PRESENTATION 0,1,1;" << std::endl;
	out << "PATHTYPE 0;" << std::endl;
	out << "STRANS 0,0,0;" << std::endl;
	out << "MAG 2.500000e-02;" << std::endl;
	out << "XY 1;" << std::endl;
	out << " X: " << x_right_boundary * 2 << 	";		 Y: -208;" << std::endl;
	out << "STRING VSS;" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Draw Gate
	int gate_tip_ver = static_cast<int>(ASAP_DR::GATE_TIP_VER);
	int gate_width = static_cast<int>(ASAP_DR::GATE_WIDTH);
	for (int i = 0; i < num_gate + 2; i++) {
		int x_left = (gate_pitch - gate_width) / 2 + gate_pitch * i;
		int x_right = x_left + gate_width;
		int y_bot = -gate_tip_ver;
		int y_top = cell_height + gate_tip_ver;

		out << "BOUNDARY;" << std::endl;
		out << "LAYER " << static_cast<int>(LAYER::GATE) << ";" << std::endl;
		out << "DATATYPE 0;" << std::endl;
		out << "XY 5;" << std::endl;
		out << " X: " << x_left * 4 << ";		 Y: " << y_bot * 4 << ";" << std::endl;
		out << " X: " << x_right * 4 << ";		 Y: " << y_bot * 4 << ";" << std::endl;
		out << " X: " << x_right * 4 << ";		 Y: " << y_top * 4 << ";" << std::endl;
		out << " X: " << x_left * 4 << ";		 Y: " << y_top * 4 << ";" << std::endl;
		out << " X: " << x_left * 4 << ";		 Y: " << y_bot * 4 << ";" << std::endl;
		out << "ENDEL;" << std::endl << std::endl;
	}	

	// *** Draw GCUT ***
	int gcut_height = static_cast<int>(ASAP_DR::GCUT_HEIGHT);
	
	// VDD-GCUT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::GCUT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: " << (cell_height - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (cell_height + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (cell_height - gcut_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// VSS-GCUT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::GCUT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: " << (- gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (- gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (- gcut_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Left-boundary GCUT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::GCUT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: 0;		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << gate_pitch * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << gate_pitch * 4 << ";		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: 0;		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Right-boundary GCUT
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::GCUT) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: " << (x_right_boundary - gate_pitch) * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << (x_right_boundary - gate_pitch) * 4 << ";		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
	out << " X: " << (x_right_boundary - gate_pitch) * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// Internal dummy gates
	int consecutive = -1;
	for (int i = 0; i < num_gate; i++) {
		if (place_sol.nmos[i].gate == "dummy" && place_sol.pmos[i].gate == "dummy") {
			if (consecutive < 0) consecutive = i;
		}
		else {
			if (consecutive >= 0) {
				// found dummy gates
				int x_left = gate_pitch * (consecutive + 1);
				int x_right = gate_pitch * (i + 1);
				// print
				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::GCUT) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY 5;" << std::endl;
				out << " X: " << x_left * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
				out << " X: " << x_right * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
				out << " X: " << x_right * 4 << ";		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
				out << " X: " << x_left * 4 << ";		 Y: " << (cell_height / 2 + gcut_height / 2) * 4 << ";" << std::endl;
				out << " X: " << x_left * 4 << ";		 Y: " << (cell_height / 2 - gcut_height / 2) * 4 << ";" << std::endl;
				out << "ENDEL;" << std::endl << std::endl;

				consecutive = -1;
			}	
		}
	}

	// Draw FIN
	int fin_height = static_cast<int>(ASAP_DR::FIN_HEIGHT);
	int fin_spacing = static_cast<int>(ASAP_DR::FIN_SPACING);

	for (int i = 0; i < 10; i++) {
		int y_bot = fin_spacing / 2 + (fin_height + fin_spacing) * i;
		int y_top = y_bot + fin_height;

		out << "BOUNDARY;" << std::endl;
		out << "LAYER " << static_cast<int>(LAYER::FIN) << ";" << std::endl;
		out << "DATATYPE 0;" << std::endl;
		out << "XY 5;" << std::endl;
		out << " X: 0;		 Y: " << y_bot * 4 << ";" << std::endl;
		out << " X: " << x_right_boundary * 4 << ";		 Y: " << y_bot * 4 << ";" << std::endl;
		out << " X: " << x_right_boundary * 4 << ";		 Y: " << y_top * 4 << ";" << std::endl;
		out << " X: 0;		 Y: " << y_top * 4 << ";" << std::endl;
		out << " X: 0;		 Y: " << y_bot * 4 << ";" << std::endl;
		out << "ENDEL;" << std::endl << std::endl;
	}


	// Draw ACTIVE
	// PMOS Region
	int active_unit = static_cast<int>(ASAP_DR::ACTIVE_UNIT);
	int min_active_height = static_cast<int>(ASAP_DR::MIN_ACTIVE_HEIGHT);
	int gate_to_active = gate_pitch - gate_width - min_active_height;
	std::vector<Point> bd_points; // (y, x)
	bool is_drawing = false;
	for (int i = 0; i < num_gate; i++) {
		if (place_sol.pmos[i].nfin > 0) {
			if (!is_drawing) { // Start drawing
				int top_y = cell_height - active_unit;
				int y = cell_height - active_unit * (place_sol.pmos[i].nfin + 1);
				int x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - min_active_height;
				bd_points.emplace_back(top_y, x);
				bd_points.emplace_back(y, x);
				is_drawing = true;
			}
			else {            // Drawing ~ing
				assert(i > 0);
				if (place_sol.pmos[i - 1].nfin != place_sol.pmos[i].nfin) { // add boundary points
					int x;
					if (place_sol.pmos[i - 1].nfin < place_sol.pmos[i].nfin) x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - min_active_height;
					else x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - gate_to_active;
					
					int prev_y = cell_height - active_unit * (place_sol.pmos[i - 1].nfin + 1);
					int curr_y = cell_height - active_unit * (place_sol.pmos[i].nfin + 1);
					bd_points.emplace_back(prev_y, x);
					bd_points.emplace_back(curr_y, x);
				}
			}
		}

		else {                // MEET DUMMY GATE
			if (is_drawing) { // Terminate drawing
				assert(i > 0);
				int x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - gate_to_active;
				int prev_y = cell_height - active_unit * (place_sol.pmos[i - 1].nfin + 1);
				int top_y = cell_height - active_unit;

				bd_points.emplace_back(prev_y, x);
				bd_points.emplace_back(top_y, x);
				bd_points.push_back(bd_points[0]);

				// Drawing
				int bd_points_size = bd_points.size();

				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::ACTIVE) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY " << bd_points_size << ";" << std::endl;
				for (int j = 0; j < bd_points_size; j++) {
					out << " X: " << bd_points[j].x * 4 << ";		 Y: " << bd_points[j].y * 4 << ";" << std::endl;
				}
				out << "ENDEL;" << std::endl << std::endl;

				bd_points.clear();
				is_drawing = false;
			}
		}

		if (i == num_gate - 1 && is_drawing) {
			int x = gate_pitch / 2 + gate_pitch * (i + 1) + gate_width / 2 + min_active_height;
			int curr_y = cell_height - active_unit * (place_sol.pmos[i].nfin + 1);
			int top_y = cell_height - active_unit;

			bd_points.emplace_back(curr_y, x);
			bd_points.emplace_back(top_y, x);
			bd_points.push_back(bd_points[0]);
		
			// Drawing
			int bd_points_size = bd_points.size();

			out << "BOUNDARY;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::ACTIVE) << ";" << std::endl;
			out << "DATATYPE 0;" << std::endl;
			out << "XY " << bd_points_size << ";" << std::endl;
			for (int j = 0; j < bd_points_size; j++) {
				out << " X: " << bd_points[j].x * 4 << ";		 Y: " << bd_points[j].y * 4 << ";" << std::endl;
			}
			out << "ENDEL;" << std::endl << std::endl;

			bd_points.clear();
			is_drawing = false;
		}
	}

	// NMOS Region
	is_drawing = false;
	for (int i = 0; i < num_gate; i++) {
		if (place_sol.nmos[i].nfin > 0) {
			if (!is_drawing) { // Start drawing
				int bot_y = active_unit;
				int y = active_unit * (place_sol.nmos[i].nfin + 1);
				int x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - min_active_height;
				bd_points.emplace_back(bot_y, x);
				bd_points.emplace_back(y, x);
				is_drawing = true;
			}
			else {            // Drawing ~ing
				assert(i > 0);
				if (place_sol.nmos[i - 1].nfin != place_sol.nmos[i].nfin) { // add boundary points
					int x;
					if (place_sol.nmos[i - 1].nfin < place_sol.nmos[i].nfin) x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - min_active_height;
					else x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - gate_to_active;
					int prev_y = active_unit * (place_sol.nmos[i - 1].nfin + 1);
					int curr_y = active_unit * (place_sol.nmos[i].nfin + 1);
					bd_points.emplace_back(prev_y, x);
					bd_points.emplace_back(curr_y, x);
				}
			}
		}

		else {                // MEET DUMMY GATE
			if (is_drawing) { // Terminate drawing
				assert(i > 0);
				int x = gate_pitch / 2 + gate_pitch * (i + 1) - gate_width / 2 - gate_to_active;
				int prev_y = active_unit * (place_sol.nmos[i - 1].nfin + 1);
				int bot_y = active_unit;

				bd_points.emplace_back(prev_y, x);
				bd_points.emplace_back(bot_y, x);
				bd_points.push_back(bd_points[0]);

				// Drawing
				int bd_points_size = bd_points.size();

				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::ACTIVE) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY " << bd_points_size << ";" << std::endl;
				for (int j = 0; j < bd_points_size; j++) {
					out << " X: " << bd_points[j].x * 4 << ";		 Y: " << bd_points[j].y * 4 << ";" << std::endl;
				}
				out << "ENDEL;" << std::endl << std::endl;

				bd_points.clear();
				is_drawing = false;
			}
		}
		if (i == num_gate - 1 && is_drawing) {
			int x = gate_pitch / 2 + gate_pitch * (i + 1) + gate_width / 2 + min_active_height;
			int curr_y = active_unit * (place_sol.nmos[i].nfin + 1);
			int bot_y = active_unit;

			bd_points.emplace_back(curr_y, x);
			bd_points.emplace_back(bot_y, x);
			bd_points.push_back(bd_points[0]);
		
			// Drawing
			int bd_points_size = bd_points.size();

			out << "BOUNDARY;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::ACTIVE) << ";" << std::endl;
			out << "DATATYPE 0;" << std::endl;
			out << "XY " << bd_points_size << ";" << std::endl;
			for (int j = 0; j < bd_points_size; j++) {
				out << " X: " << bd_points[j].x * 4 << ";		 Y: " << bd_points[j].y * 4 << ";" << std::endl;
			}
			out << "ENDEL;" << std::endl << std::endl;

			bd_points.clear();
			is_drawing = false;
		}
	}

	// Draw SDT
	std::vector<std::string> pmos_diff, nmos_diff, gate_diff;
	std::vector<int> pmos_fin, nmos_fin;
	for (int i = 0; i < num_gate; i++) {
		std::string gate_net = (place_sol.pmos[i].gate != "dummy") ? place_sol.pmos[i].gate : place_sol.nmos[i].gate;
		gate_diff.push_back(gate_net);
		
		// left diffusion
		if (i == 0) {
			pmos_diff.push_back(place_sol.pmos[i].left);
			nmos_diff.push_back(place_sol.nmos[i].left);
			pmos_fin.push_back(place_sol.pmos[i].nfin);
			nmos_fin.push_back(place_sol.nmos[i].nfin);
		}
		
		// right diffusion
		if (i != num_gate - 1) {
			std::string right_net;
			right_net = (place_sol.pmos[i].right != "dummy") ? place_sol.pmos[i].right : place_sol.pmos[i + 1].left;
			pmos_diff.push_back(right_net);
			pmos_fin.push_back(std::max(place_sol.pmos[i].nfin, place_sol.pmos[i + 1].nfin));
			
			right_net = (place_sol.nmos[i].right != "dummy") ? place_sol.nmos[i].right : place_sol.nmos[i + 1].left;
			nmos_diff.push_back(right_net);
			nmos_fin.push_back(std::max(place_sol.nmos[i].nfin, place_sol.nmos[i + 1].nfin));
		}
		else {
			pmos_diff.push_back(place_sol.pmos[i].right);
			nmos_diff.push_back(place_sol.nmos[i].right);
			pmos_fin.push_back(place_sol.pmos[i].nfin);
			nmos_fin.push_back(place_sol.nmos[i].nfin);
		}
	}

	// count number of regions per each net

	std::unordered_map<std::string, int> num_pin;
	int num_diff = pmos_diff.size();
	for (int i = 0; i < num_diff; i++) {
		if (pmos_diff[i] != "dummy") {
			if (num_pin.find(pmos_diff[i]) == num_pin.end()) num_pin[pmos_diff[i]] = 1;
			else num_pin[pmos_diff[i]]++;
		}
		if (nmos_diff[i] != "dummy") {
			if (num_pin.find(nmos_diff[i]) == num_pin.end()) num_pin[nmos_diff[i]] = 1;
			else num_pin[nmos_diff[i]]++;
		}
	}
	bool is_consecutive = false;
	for (int i = 0; i < num_gate; i++) {
		if (gate_diff[i] == "dummy") {
			if (is_consecutive) {
				if (num_pin.find(gate_diff[i - 1]) == num_pin.end()) num_pin[gate_diff[i - 1]] = 1;
				else num_pin[gate_diff[i - 1]]++;
				is_consecutive = false;
			}
		}
		else {
			if (!is_consecutive) is_consecutive = true;
			else {
				assert(i > 0);
				if (gate_diff[i] != gate_diff[i - 1]) {
					if (num_pin.find(gate_diff[i - 1]) == num_pin.end()) num_pin[gate_diff[i - 1]] = 1;
					else num_pin[gate_diff[i - 1]]++;
					is_consecutive = true;
				}
			}
		}
		if (i == num_gate - 1 && is_consecutive) {
			if (num_pin.find(gate_diff[i]) == num_pin.end()) num_pin[gate_diff[i]] = 1;
			else num_pin[gate_diff[i]]++;
		}
	}

	int sdt_width = static_cast<int>(ASAP_DR::SDT_WIDTH);

	for (int i = 0; i < num_diff; i++) {
		if ((pmos_diff[i] != "dummy" && num_pin[pmos_diff[i]] > 1) || (pmos_diff[i] == "VDD")) {
			int lx = gate_pitch * (i + 1) - sdt_width / 2;
			int rx = gate_pitch * (i + 1) + sdt_width / 2;
			int ty = cell_height - active_unit;
			int by = ty - active_unit * pmos_fin[i];

			out << "BOUNDARY;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::SDT) << ";" << std::endl;
			out << "DATATYPE 0;" << std::endl;
			out << "XY 5;" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << "ENDEL;" << std::endl << std::endl;

		}

		if ((nmos_diff[i] != "dummy" && num_pin[nmos_diff[i]] > 1) || (nmos_diff[i] == "VSS")) {
			int lx = gate_pitch * (i + 1) - sdt_width / 2;
			int rx = gate_pitch * (i + 1) + sdt_width / 2;
			int ty = active_unit * (nmos_fin[i] + 1);
			int by = active_unit;

			out << "BOUNDARY;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::SDT) << ";" << std::endl;
			out << "DATATYPE 0;" << std::endl;
			out << "XY 5;" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << "ENDEL;" << std::endl << std::endl;

		}

	}

	// Draw LISD
	int lisd_width = static_cast<int>(ASAP_DR::LISD_WIDTH);

	// Draw Active-connecting LISD first
	for (auto& active_lisd_info : mol_active) {
		std::string region = std::get<1>(active_lisd_info);
		int nfin = std::get<2>(active_lisd_info);
		int l_active = std::get<3>(active_lisd_info);
		int r_active = std::get<4>(active_lisd_info);

		int lx = gate_pitch * (l_active + 1) - lisd_width / 2;
		int rx = gate_pitch * (r_active + 1) + lisd_width / 2;

		int ty, by;

		if (region == "p") {
			ty = cell_height - active_unit;
			by = cell_height - active_unit * (nfin + 1);
		}
		else if (region == "n") {
			ty = active_unit * (nfin + 1);
			by = active_unit;
		}
		out << "BOUNDARY;" << std::endl;
		out << "LAYER " << static_cast<int>(LAYER::LISD) << ";" << std::endl;
		out << "DATATYPE 0;" << std::endl;
		out << "XY 5;" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
		out << "ENDEL;" << std::endl << std::endl;
	}

	// draw individual active's LISD
	for (int i = 0; i < num_diff; i++) {
		if ((pmos_diff[i] != "dummy" && num_pin[pmos_diff[i]] > 1) || (pmos_diff[i] == "VDD")) {
			
			bool is_indep = true;
			for (auto& active_lisd_info : mol_active) {
				std::string region = std::get<1>(active_lisd_info);
				if (region == "p") {
					int l_active = std::get<3>(active_lisd_info);
					int r_active = std::get<4>(active_lisd_info);
					if (i >= l_active && i <= r_active) {
						is_indep = false;
						break;
					}  
				}
			}
			if (is_indep) {

				int lx = gate_pitch * (i + 1) - lisd_width / 2;
				int rx = gate_pitch * (i + 1) + lisd_width / 2;
				int ty = (pmos_diff[i] == "VDD") ? (cell_height) : (cell_height - active_unit);
				int by = cell_height - active_unit * (pmos_fin[i] + 1);
				
				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::LISD) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY 5;" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << "ENDEL;" << std::endl << std::endl;
			}

		}

		if ((nmos_diff[i] != "dummy" && num_pin[nmos_diff[i]] > 1) || (nmos_diff[i] == "VSS")) {
			
			bool is_indep = true;
			for (auto& active_lisd_info : mol_active) {
				std::string region = std::get<1>(active_lisd_info);
				if (region == "n") {
					int l_active = std::get<3>(active_lisd_info);
					int r_active = std::get<4>(active_lisd_info);
					if (i >= l_active && i <= r_active) {
						is_indep = false;
						break;
					}  
				}
			}
			if (is_indep) {
				int lx = gate_pitch * (i + 1) - lisd_width / 2;
				int rx = gate_pitch * (i + 1) + lisd_width / 2;
				int ty = active_unit * (nmos_fin[i] + 1);
				int by = (nmos_diff[i] == "VSS") ? 0 : active_unit;

				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::LISD) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY 5;" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << "ENDEL;" << std::endl << std::endl;
			}
		}
	}

	// Draw LIG
	int lig_pwr_height = static_cast<int>(ASAP_DR::LIG_PWR_HEIGHT);
	int lig_center_height = static_cast<int>(ASAP_DR::LIG_CENTER_HEIGHT);

	// LIG in power rails
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::LIG) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (-lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (-lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (-lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::LIG) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height - lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height - lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height + lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height + lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height - lig_pwr_height / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	// LIG in center regions
	for (int i = 0; i < num_gate; i++) {
		std::cout << gate_diff[i] << " ";
	}
	std::cout << std::endl;

	int lig_gate = static_cast<int>(ASAP_DR::LIG_GATE);

	int s_gate = -1;
	for (int i = 0; i < num_gate; i++) {
		if (gate_diff[i] == "dummy") {
			if (s_gate >= 0) {   // s_gate ~ i-1
				int lx = gate_pitch / 2 + gate_pitch * (s_gate + 1) - gate_width / 2 - lig_gate;
				int rx = gate_pitch / 2 + gate_pitch * i + gate_width / 2 + lig_gate;
				int ty = cell_height / 2 + lig_center_height / 2;
				int by = cell_height / 2 - lig_center_height / 2;

				out << "BOUNDARY;" << std::endl;
				out << "LAYER " << static_cast<int>(LAYER::LIG) << ";" << std::endl;
				out << "DATATYPE 0;" << std::endl;
				out << "XY 5;" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
				out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
				out << "ENDEL;" << std::endl << std::endl;
				
				s_gate = -1;
			}
		}
		else {
			if (s_gate < 0) s_gate = i;
			else {
				assert(i > 0);
				if (gate_diff[i] != gate_diff[i - 1]) { // s_gate ~ i-1
					int lx = gate_pitch / 2 + gate_pitch * (s_gate + 1) - gate_width / 2 - lig_gate;
					int rx = gate_pitch / 2 + gate_pitch * i + gate_width / 2 + lig_gate;
					int ty = cell_height / 2 + lig_center_height / 2;
					int by = cell_height / 2 - lig_center_height / 2;

					out << "BOUNDARY;" << std::endl;
					out << "LAYER " << static_cast<int>(LAYER::LIG) << ";" << std::endl;
					out << "DATATYPE 0;" << std::endl;
					out << "XY 5;" << std::endl;
					out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
					out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
					out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
					out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
					out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
					out << "ENDEL;" << std::endl << std::endl;
					
					s_gate = i;
				}
			}
		}
		if (i == num_gate - 1 && s_gate >= 0) {
			int lx = gate_pitch / 2 + gate_pitch * (s_gate + 1) - gate_width / 2 - lig_gate;
			int rx = gate_pitch / 2 + gate_pitch * (i + 1) + gate_width / 2 + lig_gate;
			int ty = cell_height / 2 + lig_center_height / 2;
			int by = cell_height / 2 - lig_center_height / 2;

			out << "BOUNDARY;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::LIG) << ";" << std::endl;
			out << "DATATYPE 0;" << std::endl;
			out << "XY 5;" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << " X: " << rx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << by * 4 << ";" << std::endl;
			out << " X: " << lx * 4 << ";		 Y: " << ty * 4 << ";" << std::endl;
			out << "ENDEL;" << std::endl << std::endl;
					
			s_gate = -1;		
		}
	}

	// Draw V0
	// Boundary V0
	int v0_width = static_cast<int>(ASAP_DR::V0_WIDTH);
	for (int i = 0; i <= num_gate; i++) {
		int lx = gate_pitch * (i + 1) - v0_width / 2;
		int rx = gate_pitch * (i + 1) + v0_width / 2;

		// PMOS Region
		out << "BOUNDARY;" << std::endl;
		out << "LAYER " << static_cast<int>(LAYER::V0) << ";" << std::endl;
		out << "DATATYPE 0;" << std::endl;
		out << "XY 5;" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (cell_height + v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << (cell_height + v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << (cell_height - v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (cell_height - v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (cell_height + v0_width / 2) * 4 << ";" << std::endl;
		out << "ENDEL;" << std::endl << std::endl;

		// NMOS Region
		out << "BOUNDARY;" << std::endl;
		out << "LAYER " << static_cast<int>(LAYER::V0) << ";" << std::endl;
		out << "DATATYPE 0;" << std::endl;
		out << "XY 5;" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << (v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << rx * 4 << ";		 Y: " << (-v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (-v0_width / 2) * 4 << ";" << std::endl;
		out << " X: " << lx * 4 << ";		 Y: " << (v0_width / 2) * 4 << ";" << std::endl;
		out << "ENDEL;" << std::endl << std::endl;
	}

	int m1_width = static_cast<int>(ASAP_DR::M1_WIDTH);
	int m1_pitch = static_cast<int>(ASAP_DR::M1_PITCH);
	int m1_v0_ex = static_cast<int>(ASAP_DR::M1_V0_EX);
	int m1_t2t = static_cast<int>(ASAP_DR::M1_T2T);
	int m1_t2s = static_cast<int>(ASAP_DR::M1_T2S);

	std::vector<int> track_y;
	track_y.push_back(cell_height - active_unit - m1_width / 2);
	track_y.push_back(cell_height - active_unit - m1_width / 2 - m1_pitch);
	track_y.push_back(cell_height / 2);
	track_y.push_back(active_unit + m1_width / 2 + m1_pitch);
	track_y.push_back(active_unit + m1_width / 2);
	

	// Draw VDD, VSS M1
	// LIG in power rails
	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (-m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (-m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (-m1_width / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;

	out << "BOUNDARY;" << std::endl;
	out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
	out << "DATATYPE 0;" << std::endl;
	out << "XY 5;" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height - m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height - m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << x_right_boundary * 4 << ";		 Y: " << (cell_height + m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height + m1_width / 2) * 4 << ";" << std::endl;
	out << " X: " << 0 << ";		 Y: " << (cell_height - m1_width / 2) * 4 << ";" << std::endl;
	out << "ENDEL;" << std::endl << std::endl;


	// Print nets
	for (auto& it : routing_result) {
		std::string net_name = it.first;
		auto route = it.second;

		if (net_name == "overall") continue;

		// I/O pin?
		if (route->is_IO) {
			int y = 2;
			bool is_printed = false;
			for (int x = 0; x < col_size; x++) {
				if (route->via_grid[0][y][x] == 1) {
					int cy = track_y[y];
					int cx = gate_pitch / 2 * (x + 1);

					assert(route->metal_grid[0][y][x] == 1);

					// Draw V0
					out << "BOUNDARY;" << std::endl;
					out << "LAYER " << static_cast<int>(LAYER::V0) << ";" << std::endl;
					out << "DATATYPE 0;" << std::endl;
					out << "XY 5;" << std::endl;
					out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
					out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
					out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
					out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
					out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
					out << "ENDEL;" << std::endl << std::endl;

					int io_pin_height_half = track_y[1] - track_y[2] - m1_width / 2 - m1_t2s;

					int io_pin_height_top = io_pin_height_half;
					int io_pin_height_bot = io_pin_height_half;

					if (routing_result["overall"]->metal_grid[0][1][x] == 0) {
						if (x > 0 && routing_result["overall"]->metal_grid[0][1][x - 1] == 0) {
							if (x < col_size - 1 && routing_result["overall"]->metal_grid[0][1][x + 1] == 0) {
								io_pin_height_top += m1_pitch;
								if (routing_result["overall"]->metal_grid[0][0][x] == 0) {
									if (x > 0 && routing_result["overall"]->metal_grid[0][0][x - 1] == 0) {
										if (x < col_size - 1 && routing_result["overall"]->metal_grid[0][0][x + 1] == 0) {
											io_pin_height_top += m1_pitch;
										}
									}
								}
							}
						}
					}

					if (routing_result["overall"]->metal_grid[0][3][x] == 0) {
						if (x > 0 && routing_result["overall"]->metal_grid[0][3][x - 1] == 0) {
							if (x < col_size - 1 && routing_result["overall"]->metal_grid[0][3][x + 1] == 0) {
								io_pin_height_bot += m1_pitch;
								if (routing_result["overall"]->metal_grid[0][4][x] == 0) {
									if (x > 0 && routing_result["overall"]->metal_grid[0][4][x - 1] == 0) {
										if (x < col_size - 1 && routing_result["overall"]->metal_grid[0][4][x + 1] == 0) {
											io_pin_height_bot += m1_pitch;
										}
									}
								}
							}
						}
					}


					/*
					if (routing_result["overall"]->metal_grid[0][1][x] == 0) {
						io_pin_height_top += m1_pitch;
						if (routing_result["overall"]->metal_grid[0][0][x] == 0) io_pin_height_top += m1_pitch;
					}
					if (routing_result["overall"]->metal_grid[0][3][x] == 0) {
						io_pin_height_bot += m1_pitch;
						if (routing_result["overall"]->metal_grid[0][4][x] == 0) io_pin_height_bot += m1_pitch;
					}*/


					// Draw I/O pin
					out << "BOUNDARY;" << std::endl;
					out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
					out << "DATATYPE 0;" << std::endl;
					out << "XY 5;" << std::endl;
					out << " X: " << (cx - m1_width / 2) * 4 << ";		 Y: " << (cy + io_pin_height_top) * 4 << ";" << std::endl;
					out << " X: " << (cx + m1_width / 2) * 4 << ";		 Y: " << (cy + io_pin_height_top) * 4 << ";" << std::endl;
					out << " X: " << (cx + m1_width / 2) * 4 << ";		 Y: " << (cy - io_pin_height_bot) * 4 << ";" << std::endl;
					out << " X: " << (cx - m1_width / 2) * 4 << ";		 Y: " << (cy - io_pin_height_bot) * 4 << ";" << std::endl;
					out << " X: " << (cx - m1_width / 2) * 4 << ";		 Y: " << (cy + io_pin_height_top) * 4 << ";" << std::endl;
					out << "ENDEL;" << std::endl << std::endl;

				}
			}
		}

		// not I/O pin
		else {
			// draw V0 & V1
			for (int y = 0; y < row_size; y++) {
				for (int x = 0; x < col_size; x++) {
					if (route->via_grid[0][y][x] == 1) {
						int cy = track_y[y];
						int cx = gate_pitch / 2 * (x + 1);

						out << "BOUNDARY;" << std::endl;
						out << "LAYER " << static_cast<int>(LAYER::V0) << ";" << std::endl;
						out << "DATATYPE 0;" << std::endl;
						out << "XY 5;" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << "ENDEL;" << std::endl << std::endl;
					}
					if (route->via_grid[1][y][x] == 1) {
						int cy = track_y[y];
						int cx = gate_pitch / 2 * (x + 1);

						out << "BOUNDARY;" << std::endl;
						out << "LAYER " << static_cast<int>(LAYER::V1) << ";" << std::endl;
						out << "DATATYPE 0;" << std::endl;
						out << "XY 5;" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx + v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy - v0_width / 2) * 4 << ";" << std::endl;
						out << " X: " << (cx - v0_width / 2) * 4 << ";		 Y: " << (cy + v0_width / 2) * 4 << ";" << std::endl;
						out << "ENDEL;" << std::endl << std::endl;

					}
				}
			}

			// draw M1
			// Find metal component through DFS
			std::vector<std::vector<bool>> explored;
			explored.resize(row_size);
			for (int i = 0; i < row_size; i++) {
				explored[i].resize(col_size);
				for (int j = 0; j < col_size; j++) explored[i][j] = false;
			}

			for (int y = 0; y < row_size; y++) {
				for (int x = 0; x < col_size; x++) {
					if (route->metal_grid[0][y][x] == 1 && !explored[y][x]) {
						
						std::vector<Point> component_points;

						// Find connected components
						DFS_Metal(route, component_points, y, x, explored, 0);
						
						// Find boundary points
						std::vector<std::tuple<Point, bool, bool, bool, bool>> boundary_points;
						for (auto& point : component_points) {
							// hor, ver both exist or only one direction

							bool left =  (point.x > 0 && route->hor_grid[0][point.y][point.x - 1] == 1) ? true : false; 
							bool right = (point.x < col_size - 1 && route->hor_grid[0][point.y][point.x] == 1) ? true : false;
							bool up = (point.y > 0 && route->ver_grid[0][point.y - 1][point.x] == 1) ? true : false;
							bool down = (point.y < row_size - 1 && route->ver_grid[0][point.y][point.x] == 1) ? true : false;

							int cy = track_y[point.y];
							int cx = gate_pitch / 2 * (point.x + 1);

							assert(left || right || up || down);

							int hor_dir = 0, ver_dir = 0;
							if (left) hor_dir++;
							if (right) hor_dir++;
							if (up) ver_dir++;
							if (down) ver_dir++;

							if (!((hor_dir > 0 && ver_dir > 0) || hor_dir + ver_dir == 1)) continue;

							// End point	
							if (left && !right && !up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2 + m1_v0_ex), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2 + m1_v0_ex), true, false, false, true));
							}
							else if (!left && right && !up  && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2 - m1_v0_ex), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2 - m1_v0_ex), false, true, false, true));
							}
							else if (!left && !right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2 - m1_v0_ex, cx - m1_width / 2), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2 - m1_v0_ex, cx + m1_width / 2), true, false, true, false));
							}
							else if (!left && !right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2 + m1_v0_ex, cx - m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2 + m1_v0_ex, cx + m1_width / 2), true, false, false, true));
							}						
						
							// two-direction points
							else if (left && !right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), true, false, true, false));
							}
							else if (!left && right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), false, true, true, false));
							}
							else if (left && !right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
							}
							else if (!left && right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
							}

							// three-direction points
							else if (left && right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
							}
							else if (!left && right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
							}
							else if (left && right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
							}
							else if (left && !right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
							}

							// four-direction points
							else if (left && right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
			
							}
						}

						// Circulate
						std::vector<Point> cir_boundary;
						cir_boundary.push_back(std::get<0>(boundary_points[0]));
						
						// Left, Right, Up, Down
						int to_direction = (std::get<1>(boundary_points[0])) ? 0 : ((std::get<2>(boundary_points[0])) ? 1 : 2);

						Point previous_point = std::get<0>(boundary_points[0]);

						int n_boundary_points = boundary_points.size();
						std::vector<bool> visited(n_boundary_points, false);
						
						for (int i = 0; i < n_boundary_points; i++) {
							// Find next point index

							int next_pt_idx = -1;
							int dist = 99999999;
							for (int j = 0; j < n_boundary_points; j++) {
								auto& next_cand_point = std::get<0>(boundary_points[j]);

								if (visited[j]) continue;
								if (to_direction == 0 && previous_point.x > next_cand_point.x && previous_point.y == next_cand_point.y) {
									if (dist > std::abs(previous_point.x - next_cand_point.x)) {
										dist = std::abs(previous_point.x - next_cand_point.x);
										next_pt_idx = j;
									}									
								}
								if (to_direction == 1 && previous_point.x < next_cand_point.x && previous_point.y == next_cand_point.y) {
									if (dist > std::abs(previous_point.x - next_cand_point.x)) {
										dist = std::abs(previous_point.x - next_cand_point.x);
										next_pt_idx = j;
									}									
								}
								if (to_direction == 2 && previous_point.y < next_cand_point.y && previous_point.x == next_cand_point.x) {
									if (dist > std::abs(previous_point.y - next_cand_point.y)) {
										dist = std::abs(previous_point.y - next_cand_point.y);
										next_pt_idx = j;
									}													
								}
								if (to_direction == 3 && previous_point.y > next_cand_point.y && previous_point.x == next_cand_point.x) {
									if (dist > std::abs(previous_point.y - next_cand_point.y)) {
										dist = std::abs(previous_point.y - next_cand_point.y);
										next_pt_idx = j;
									}													
								}
							}

							if (next_pt_idx == -1) {
								std::cout << "Cannot find next points" << std::endl;
								exit(0);
							}
							cir_boundary.push_back(std::get<0>(boundary_points[next_pt_idx]));
							visited[next_pt_idx] = true;
						
							previous_point = std::get<0>(boundary_points[next_pt_idx]);
							if (to_direction == 0 || to_direction == 1) {
								if (std::get<3>(boundary_points[next_pt_idx])) to_direction = 2;
								else if (std::get<4>(boundary_points[next_pt_idx])) to_direction = 3;
								else {
									std::cout << "Direction Error!" << std::endl;
									exit(0);
								}
							}
							else if (to_direction == 2 || to_direction == 3) {
								if (std::get<1>(boundary_points[next_pt_idx])) to_direction = 0;
								else if (std::get<2>(boundary_points[next_pt_idx])) to_direction = 1;
								else {
									std::cout << "Direction Error!" << std::endl;
									exit(0);
								}
							}
							else {
								std::cout << "Direction Out of bound!" << std::endl;
								exit(0);
							}
						
						}

						// Draw M1

						out << "BOUNDARY;" << std::endl;
						out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
						out << "DATATYPE 0;" << std::endl;
						out << "XY "<< static_cast<int>(cir_boundary.size()) << " ;" << std::endl;
						for (int i = 0; i < cir_boundary.size(); i++) {
							out << " X: " << cir_boundary[i].x * 4 << ";		 Y: " << cir_boundary[i].y * 4 << ";" << std::endl;
						}
						out << "ENDEL;" << std::endl << std::endl;
					}
				}
			}

			// draw M2
			// Find metal component through DFS
			for (int i = 0; i < row_size; i++) {
				for (int j = 0; j < col_size; j++) explored[i][j] = false;
			}

			for (int y = 0; y < row_size; y++) {
				for (int x = 0; x < col_size; x++) {
					if (route->metal_grid[1][y][x] == 1 && !explored[y][x]) {
						
						std::vector<Point> component_points;

						// Find connected components
						DFS_Metal(route, component_points, y, x, explored, 1);
						
						// Find boundary points
						std::vector<std::tuple<Point, bool, bool, bool, bool>> boundary_points;
						for (auto& point : component_points) {
							// hor, ver both exist or only one direction

							bool left =  (point.x > 0 && route->hor_grid[1][point.y][point.x - 1] == 1) ? true : false; 
							bool right = (point.x < col_size - 1 && route->hor_grid[1][point.y][point.x] == 1) ? true : false;
							bool up = (point.y > 0 && route->ver_grid[1][point.y - 1][point.x] == 1) ? true : false;
							bool down = (point.y < row_size - 1 && route->ver_grid[1][point.y][point.x] == 1) ? true : false;

							int cy = track_y[point.y];
							int cx = gate_pitch / 2 * (point.x + 1);

							assert(left || right || up || down);

							int hor_dir = 0, ver_dir = 0;
							if (left) hor_dir++;
							if (right) hor_dir++;
							if (up) ver_dir++;
							if (down) ver_dir++;

							if (!((hor_dir > 0 && ver_dir > 0) || hor_dir + ver_dir == 1)) continue;

							// End point	
							if (left && !right && !up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2 + m1_v0_ex), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2 + m1_v0_ex), true, false, false, true));
							}
							else if (!left && right && !up  && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2 - m1_v0_ex), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2 - m1_v0_ex), false, true, false, true));
							}
							else if (!left && !right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2 - m1_v0_ex, cx - m1_width / 2), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2 - m1_v0_ex, cx + m1_width / 2), true, false, true, false));
							}
							else if (!left && !right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2 + m1_v0_ex, cx - m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2 + m1_v0_ex, cx + m1_width / 2), true, false, false, true));
							}						
						
							// two-direction points
							else if (left && !right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), true, false, true, false));
							}
							else if (!left && right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), false, true, true, false));
							}
							else if (left && !right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
							}
							else if (!left && right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
							}

							// three-direction points
							else if (left && right && up && !down) {
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
							}
							else if (!left && right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
							}
							else if (left && right && !up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
							}
							else if (left && !right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
							}

							// four-direction points
							else if (left && right && up && down) {
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx - m1_width / 2), true, false, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx - m1_width / 2), true, false, true, false));
								boundary_points.push_back(std::make_tuple(Point(cy - m1_width / 2, cx + m1_width / 2), false, true, false, true));
								boundary_points.push_back(std::make_tuple(Point(cy + m1_width / 2, cx + m1_width / 2), false, true, true, false));
			
							}
						}

						// Circulate
						std::vector<Point> cir_boundary;
						cir_boundary.push_back(std::get<0>(boundary_points[0]));
						
						// Left, Right, Up, Down
						int to_direction = (std::get<1>(boundary_points[0])) ? 0 : ((std::get<2>(boundary_points[0])) ? 1 : 2);

						Point previous_point = std::get<0>(boundary_points[0]);

						int n_boundary_points = boundary_points.size();
						std::vector<bool> visited(n_boundary_points, false);
						
						for (int i = 0; i < n_boundary_points; i++) {
							// Find next point index

							int next_pt_idx = -1;
							int dist = 99999999;
							for (int j = 0; j < n_boundary_points; j++) {
								auto& next_cand_point = std::get<0>(boundary_points[j]);

								if (visited[j]) continue;
								if (to_direction == 0 && previous_point.x > next_cand_point.x && previous_point.y == next_cand_point.y) {
									if (dist > std::abs(previous_point.x - next_cand_point.x)) {
										dist = std::abs(previous_point.x - next_cand_point.x);
										next_pt_idx = j;
									}									
								}
								if (to_direction == 1 && previous_point.x < next_cand_point.x && previous_point.y == next_cand_point.y) {
									if (dist > std::abs(previous_point.x - next_cand_point.x)) {
										dist = std::abs(previous_point.x - next_cand_point.x);
										next_pt_idx = j;
									}									
								}
								if (to_direction == 2 && previous_point.y < next_cand_point.y && previous_point.x == next_cand_point.x) {
									if (dist > std::abs(previous_point.y - next_cand_point.y)) {
										dist = std::abs(previous_point.y - next_cand_point.y);
										next_pt_idx = j;
									}													
								}
								if (to_direction == 3 && previous_point.y > next_cand_point.y && previous_point.x == next_cand_point.x) {
									if (dist > std::abs(previous_point.y - next_cand_point.y)) {
										dist = std::abs(previous_point.y - next_cand_point.y);
										next_pt_idx = j;
									}													
								}
							}

							if (next_pt_idx == -1) {
								std::cout << "Cannot find next points" << std::endl;
								exit(0);
							}
							cir_boundary.push_back(std::get<0>(boundary_points[next_pt_idx]));
							visited[next_pt_idx] = true;
						
							previous_point = std::get<0>(boundary_points[next_pt_idx]);
							if (to_direction == 0 || to_direction == 1) {
								if (std::get<3>(boundary_points[next_pt_idx])) to_direction = 2;
								else if (std::get<4>(boundary_points[next_pt_idx])) to_direction = 3;
								else {
									std::cout << "Direction Error!" << std::endl;
									exit(0);
								}
							}
							else if (to_direction == 2 || to_direction == 3) {
								if (std::get<1>(boundary_points[next_pt_idx])) to_direction = 0;
								else if (std::get<2>(boundary_points[next_pt_idx])) to_direction = 1;
								else {
									std::cout << "Direction Error!" << std::endl;
									exit(0);
								}
							}
							else {
								std::cout << "Direction Out of bound!" << std::endl;
								exit(0);
							}
						
						}

						// Draw M2

						out << "BOUNDARY;" << std::endl;
						out << "LAYER " << static_cast<int>(LAYER::M2) << ";" << std::endl;
						out << "DATATYPE 0;" << std::endl;
						out << "XY "<< static_cast<int>(cir_boundary.size()) << " ;" << std::endl;
						for (int i = 0; i < cir_boundary.size(); i++) {
							out << " X: " << cir_boundary[i].x * 4 << ";		 Y: " << cir_boundary[i].y * 4 << ";" << std::endl;
						}
						out << "ENDEL;" << std::endl << std::endl;
					}
				}
			}
		}
	}

	// Print I/O pin text
	for (auto& net : cell.IOnets) {
		if (net == "VDD") {
			// Label VDD
			out << "TEXT;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
			out << "TEXTTYPE 251;" << std::endl;
			out << "PRESENTATION 0,1,1;" << std::endl;
			out << "PATHTYPE 0;" << std::endl;
			out << "STRANS 0,0,0;" << std::endl;
			out << "MAG 5.000000e-02;" << std::endl;
			out << "XY 1;" << std::endl;
			out << " X: " << x_right_boundary * 2 << 	";		 Y: " << cell_height * 4 << ";" << std::endl;
			out << "STRING VDD;" << std::endl;
			out << "ENDEL;" << std::endl << std::endl;
		}
		else if (net == "VSS") {
			// Label VSS
			out << "TEXT;" << std::endl;
			out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
			out << "TEXTTYPE 251;" << std::endl;
			out << "PRESENTATION 0,1,1;" << std::endl;
			out << "PATHTYPE 0;" << std::endl;
			out << "STRANS 0,0,0;" << std::endl;
			out << "MAG 5.000000e-02;" << std::endl;
			out << "XY 1;" << std::endl;
			out << " X: " << x_right_boundary * 2 << 	";		 Y: " << 0 << ";" << std::endl;
			out << "STRING VSS;" << std::endl;
			out << "ENDEL;" << std::endl << std::endl;			
		}
		else {
			auto result = routing_result[net];
			bool is_printed = false;
			for (int y = 0; y < row_size; y++) {
				for (int x = 0; x < col_size; x++) {
					if (result->metal_grid[0][y][x] == 1) {
						int cy = track_y[y];
						int cx = gate_pitch / 2 * (x + 1);

						out << "TEXT;" << std::endl;
						out << "LAYER " << static_cast<int>(LAYER::M1) << ";" << std::endl;
						out << "TEXTTYPE 251;" << std::endl;
						out << "PRESENTATION 0,1,1;" << std::endl;
						out << "PATHTYPE 0;" << std::endl;
						out << "STRANS 0,0,0;" << std::endl;
						out << "MAG 5.000000e-02;" << std::endl;
						out << "XY 1;" << std::endl;
						out << " X: " << cx * 4 << 	";		 Y: " << cy * 4 << ";" << std::endl;
						out << "STRING " << net << ";" << std::endl;
						out << "ENDEL;" << std::endl << std::endl;			
						is_printed = true;
						break;
					}
				}
				if (is_printed) break;
			}

		}
	}



	// END ASCII
	out << "ENDSTR;" << std::endl;
	out << "ENDLIB;" << std::endl;


}

void Router::DFS_Metal (std::shared_ptr<RoutingResult> route, std::vector<Point>& components, int y, int x, std::vector<std::vector<bool>>& explored, int metal_layer) {
	
	explored[y][x] = true;
	components.emplace_back(y, x);

	// Left?
	if (x > 0 && route->hor_grid[metal_layer][y][x - 1] == 1 && !explored[y][x - 1]) {
		DFS_Metal(route, components, y, x - 1, explored, metal_layer);
	} 

	// Right?
	if (x < col_size - 1 && route->hor_grid[metal_layer][y][x] == 1 && !explored[y][x + 1]) {
		DFS_Metal(route, components, y, x + 1, explored, metal_layer);
	}

	// Up?
	if (y > 0 && route->ver_grid[metal_layer][y - 1][x] == 1 && !explored[y - 1][x]) {
		DFS_Metal(route, components, y - 1, x, explored, metal_layer);
	}

	// Down?
	if (y < row_size - 1 && route->ver_grid[metal_layer][y][x] == 1 && !explored[y + 1][x]) {
		DFS_Metal(route, components, y + 1, x, explored, metal_layer);
	}

}




void Router::ascii_to_gdsii(fs::path ascii_path) {
	std::string run_gds = "java -jar ./csyn_fp/ascii2gdsii.jar < " + ascii_path.string();
	auto gds_path = ascii_path.replace_extension(fs::path(".gds"));
	std::cout << gds_path << std::endl;
	std::string mv_gds = "mv DEFAULT.gds " + gds_path.string();

	//std::cout << run_gds << std::endl;
	//std::cout << mv_gds << std::endl;
	system(run_gds.c_str());
	system(mv_gds.c_str());
}
