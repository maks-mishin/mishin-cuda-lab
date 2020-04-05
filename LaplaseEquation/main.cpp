#pragma once

#include <fstream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Grid.h"
#include "calculation.h"

using namespace std;


class TaskLaplase
{
public:
	TaskLaplase(double _a, double _b, double _dx, double _dy);
	~TaskLaplase();

	//*************init_condition
	void set_init_condition();
	void write_values();
	void compute_on_host(double eps = 0.0001);
	void compute_on_device();

private:
	double *U_s;
	double *U_s1;
	double *norm_host;

	int a, b; //Boundary x and y

	int N, M;

	GridHeat grid;
};

//Constructor
TaskLaplase::TaskLaplase(double _a, double _b, double _dx, double _dy)
{
	grid = GridHeat(_a, _b, _dx, _dy);

	set_init_condition();
}


TaskLaplase::~TaskLaplase()
{
}

//Initial conditions
void TaskLaplase::set_init_condition()
{
	N = grid.get_steps_x() - 1;
	M = grid.get_steps_y() - 1;

	U_s = new double[N*M];
	U_s1 = new double[N*M];
	norm_host = new double[N*M];

	std::vector<double> _grid_x = grid.get_grid_x();
	std::vector<double> _grid_y = grid.get_grid_y();


	//Init begin array
	for (int i = 0; i < N; i++)
	{
		double y = _grid_y.at(i);
		U_s[i] = 1;
		U_s[i*N] = exp(1 - y); //!!!!!!!!!!!!!Error
	}

	for (int i = 0; i < N; i++)
	{
		double x = _grid_x.at(i);
		U_s[i*N + M - 1] = 1;
		U_s[N*(N - 1) + i] = exp(1 - x);
	}

	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < M - 1; j++)
		{
			U_s[i*N + j] = 0.0;
		}

	//Init array for result
	for (int i = 0; i<N*N; i++)
	{
		U_s1[i] = U_s[i];
	}
}

//Function for write values to text file
void TaskLaplase::write_values()
{
	ofstream out("host_Laplase.txt");

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			out << fixed << setprecision(5) << U_s1[i*N + j] << "  ";
		}
		out << endl;
	}
}

void TaskLaplase::compute_on_host(const double eps)
{
	double max = 1;
	double *tmp;

	while (max > eps)
	{

		solver_host(U_s, U_s1, N);
		find_max(U_s, U_s1, norm_host, N);

		max = norm_host[0];

		for (int i = 0; i < N*N; i++)
		{
			if (norm_host[i] > max)
				max = norm_host[i];
		}

		tmp = U_s;
		U_s = U_s1;
		U_s1 = tmp;
	}
}


int main()
{
	const int N = 10;
	double start_execution_time = 0.0;
	double end_execution_time = 0.0;

	start_execution_time = clock();

	TaskLaplase task(1.0, 1.0, 0.01, 0.01);
	
	task.compute_on_host();
	task.write_values();
	end_execution_time = clock();
	
	std::cout << "Execution time on Host = " << (double)(end_execution_time - start_execution_time) / CLOCKS_PER_SEC << std::endl;



	return 0;
}

