#pragma once

#include <vector>

class GridHeat
{
public:
	GridHeat(double _a = 1, double _b = 1, double _dx = 0.1, double _dy = 0.1);
	~GridHeat();

	std::vector<double> get_grid_x() { return grid_x; }
	std::vector<double> get_grid_y() { return grid_y; }

	std::vector<double> grid_x;
	std::vector<double> grid_y;

	int get_steps_x() { return steps_x; }
	int get_steps_y() { return steps_y; }

	// Step on X and Y
	double dx, dy;

	//Amount of steps on X and Y
	int steps_x = 0, steps_y = 0;

	//Boundary of area
	double a, b;
};

