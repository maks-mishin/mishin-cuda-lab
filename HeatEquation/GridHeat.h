#pragma once

#include <vector>

class GridHeat
{
public:
	GridHeat(double _a = 1, double _b = 1, double _dx = 0.1, double _dy = 0.1);
	~GridHeat();

	// Step on X and Y
	double dx, dy;

	//Amount of steps on X and Y
	int steps_x = 0, steps_y = 0;

	//Boundary of area
	double a, b;
};

