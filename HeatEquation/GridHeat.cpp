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
	steps_x = 0;
	steps_y = 0;

	for (double i = 0; i < a; i += dx)
	{
		grid_x.push_back(i);
		steps_x++;
	}

	for (double i = 0; i < b; i += dy)
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

// Function for write three-dimensional grid to file
void GridHeat::writeGrid(std::string file_name)
{
	std::ofstream out;
	out.open(file_name);
	if (out.is_open())
	{
		for (int i = 0; i < steps_x; i++)
		{
			for (int j = 0; j < steps_y; j++)
			{
				out << grid_x[i] << " " << grid_y[j] << std::endl;
				if (j == steps_y - 1)
					out << std::endl << std::endl;
			}
		}
	}
	else
		std::cout << "File " << file_name << " is not open." << std::endl;

	out.close();
}
