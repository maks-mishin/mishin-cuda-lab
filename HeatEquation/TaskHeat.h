#pragma once
#include "GridHeat.h"

class TaskHeat
{
public:
	TaskHeat(double _time_max);
	~TaskHeat();

	void setInitConditions();
	void compute_on_device();
	void compute_on_host();

	void writeValues(/*double time*/);

private:
	GridHeat grid;

	int size_x, size_y;

	double *u;
	double *old_u;
	double *new_u;

	double *tmp;

	double *u_d;
	double *new_u_d;


	double time_max;
	double dt;
};

void calc_u(double *new_u, const double *u, const double tau, const double const_x, const double const_y, const int size_x, const int size_y);
