#pragma once

#include "global.h"
#include "z3++.h"

class Grid_vertex;
class Grid_edge;


class Grid_vertex {
public:
	Grid_vertex() {
		row_index = -1;
		col_index = -1;

		top_edge = nullptr;
		bottom_edge = nullptr;
		left_edge = nullptr;
		right_edge = nullptr;
	}

public:
	int row_index;
	int col_index;

	Grid_edge* top_edge;
	Grid_edge* bottom_edge;
	Grid_edge* left_edge;
	Grid_edge* right_edge;
};

class Grid_edge {
public:
	Grid_edge() {
		index = -1;

		capacity = 0;

		for (int i = 0; i < 2; i++) {
			connected_v[i] = nullptr;
		}
	}

public:
	int index;

	int capacity;
	Grid_vertex* connected_v[2];	// Does not need to delete.
};
