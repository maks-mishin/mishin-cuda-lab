#pragma once

#include "../HeatEquation/GridHeat.h"

class TaksLaplase
{
public:
	TaksLaplase(double _a, double _b, double _dx, double _dy);
	~TaksLaplase();

	void set_init_conditions();
	void set_boundary_conditions();

	void write_values();

private:
	double eps;
	GridHeat grid;

	int size_x, size_y;

	double *U_s = nullptr;
	double *U_s1 = nullptr;
};

