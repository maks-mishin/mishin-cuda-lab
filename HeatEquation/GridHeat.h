#pragma once

#include <vector>

class GridHeat
{
public:
	GridHeat(double a = 1, double b = 1, double dx = 0.1, double dy = 0.1);
	~GridHeat();

	// Function for write three-dimensional grid to file
	void writeGrid(std::string);

	//Three-dimensional grid X and Y
	std::vector<double> grid_x;
	std::vector<double> grid_y;

	// Step on X and Y
	double dx, dy;

	//Amount of steps on X and Y
	int steps_x, steps_y;

	//Boundary of area
	double a, b;
};

