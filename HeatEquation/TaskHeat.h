#pragma once
#include "GridHeat.h"

class TaskHeat
{
public:
	TaskHeat(double _time_max);
	~TaskHeat();

	void set_init_conditions();
	void compute_on_host();
	void compute_on_device();

	void write_values();


private:
	GridHeat grid;

	int size_x, size_y;

	double *U_n = nullptr;
	double *U_n1 = nullptr;
	double *tmp = nullptr;

	double time_max;
	double dt;
};