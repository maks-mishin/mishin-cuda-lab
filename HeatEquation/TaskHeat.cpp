#include <fstream>
#include "TaskHeat.h"
#include <iostream>
#include "calculation.h"

TaskHeat::TaskHeat(double _time_max)
{
	time_max = _time_max;
	grid = GridHeat(1.0, 1.0, 0.1, 0.1);

	set_init_conditions();
}

TaskHeat::~TaskHeat()
{

}

void TaskHeat::set_init_conditions()
{
	size_x = grid.steps_x;
	size_y = grid.steps_y;

	U_n = new double[size_x*size_y];
	U_n1 = new double[size_x*size_y];

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			U_n[i*size_x + j] = 0.0;
			U_n1[i*size_x + j] = 0.0;

			if (i == j && size_x/2 == i)
			{
				U_n[i*size_x + j] = 1.0;
			}
		}
	}
}

void TaskHeat::compute_on_device()
{
	//Implementation is expected here
}

void TaskHeat::compute_on_host()
{
	dt = grid.dx * grid.dy;

	double current_time = 0.0;
	do
	{
		//std::cout << "Time: " << current_time << std::endl;
		if (time_max - current_time < dt)
			dt = time_max - current_time;

		heat_step_host(U_n1, U_n, dt, 1/grid.dx*grid.dx, 1/grid.dy*grid.dy, size_x, size_y);
		
		tmp = U_n;
		U_n = U_n1;
		U_n1 = tmp;

		current_time += dt;
		
	} while (current_time  < time_max);
}

void TaskHeat::write_values()
{
	std::ofstream out;

	out.open("values.txt");

	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
		{
			out << U_n[i*size_x + j] << " ";
			if (j == size_y - 1)
			{
				out << std::endl;
			}
		}

	out.close();
}