#pragma once
#include "global.h"

class RoutingResult {
public:
    using Grid3D = std::vector<std::vector<std::vector<int>>>;

    RoutingResult() {}
    RoutingResult (int n_routing_layer, int n_row, int n_col, bool is_IO_) {
        // Allocate metal grid (2 * n_routing_layers) Ex) M1, M2
        metal_grid.resize(n_routing_layer);
        for (int z = 0; z < n_routing_layer; z++) {
            metal_grid[z].resize(n_row);
            for (int y = 0; y < n_row; y++) {
                metal_grid[z][y].resize(n_col);
                for (int x = 0; x < n_col; x++) metal_grid[z][y][x] = 0;
            }
        }

        // Allocate hor grid
        hor_grid.resize(n_routing_layer);
        for (int z = 0; z < n_routing_layer; z++) {
            hor_grid[z].resize(n_row);
            for (int y = 0; y < n_row; y++) {
                hor_grid[z][y].resize(n_col - 1);
                for (int x = 0; x < n_col - 1; x++) hor_grid[z][y][x] = 0;
            }
        }

        // Allocate ver grid
        ver_grid.resize(n_routing_layer);
        for (int z = 0; z < n_routing_layer; z++) {
            ver_grid[z].resize(n_row - 1);
            for (int y = 0; y < n_row - 1; y++) {
                ver_grid[z][y].resize(n_col);
                for (int x = 0; x < n_col; x++) ver_grid[z][y][x] = 0;
            }
        }

        // Allocate via grid
        via_grid.resize(n_routing_layer);
        for (int z = 0; z < n_routing_layer; z++) {
            via_grid[z].resize(n_row);
            for (int y = 0; y < n_row; y++) {
                via_grid[z][y].resize(n_col);
                for (int x = 0; x < n_col; x++) via_grid[z][y][x] = 0;
            }
        }

        is_IO = is_IO_;
    }

    //void initialize_grid (int n_routing_layer, int n_row, int n_col, bool is_IO_);

public:
    Grid3D metal_grid, hor_grid, ver_grid, via_grid;
    bool is_IO;
};