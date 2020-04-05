#include <iostream>
#include <fstream>
#include <string>
#include "GridHeat.h"


//Initialize grid
GridHeat::GridHeat(double _a, double _b, double _dx, double _dy)
{
	a = _a;
	b = _b;

	dx = _dx;
	dy = _dy;
	
	for (double i = 0; i < a; i += dx)
	{
		grid_x.push_back(i);
		steps_x++;
	}

	for (double i = 0; i < b; i += dx)
	{
		grid_y.push_back(i);
		steps_y++;
	}

	grid_x.push_back(a);
	grid_y.push_back(b);
	steps_x++;
	steps_y++;
}

GridHeat::~GridHeat()
{
}

