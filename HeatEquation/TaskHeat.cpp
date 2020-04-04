#include <fstream>
#include "TaskHeat.h"

//#define u(i, j) u[(i)*n + (j)]
//#define new_u(i, j) new_u[(i)*n + (j)]

TaskHeat::TaskHeat(double _time_max)
{
	time_max = _time_max;
	grid = GridHeat(1.0, 1.0, 0.1, 0.1);
	setInitConditions();
}

TaskHeat::~TaskHeat()
{
}

void TaskHeat::setInitConditions()
{
	size_x = grid.steps_x;
	size_y = grid.steps_y;

	u = new double[size_x*size_y];
	new_u = new double[size_x*size_y];

	u_d = new double[size_x*size_y];
	new_u_d = new double[size_x*size_y];

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			u[i*size_x + j] = 0.0;

			if (grid.grid_x[i] == 0.5 && grid.grid_y[j] == 0.5)
			{
				u[i*size_x + j] = 1.0;
			}
		}
	}

	//grid.writeGrid("grid.txt");
}

void TaskHeat::compute_on_device()
{
	//Implementation is expected here
}

void TaskHeat::compute_on_host()
{

	dt = sqrt(grid.dx * grid.dy + grid.dx * grid.dy);

	double current_time = 0.0;
	do
	{
		if (time_max - current_time < dt)
			dt = time_max - current_time;

		calc_u(new_u, u, dt, 1/grid.dx*grid.dx, 1/grid.dy*grid.dy, size_x, size_y);
		
		tmp = u;
		u = new_u;
		new_u = tmp;

		current_time += dt;
		
	} while (current_time  < time_max);
}

void TaskHeat::writeValues(/*double time*/)
{
	std::ofstream out;

	out.open("U.txt");

	//out << "time :" << time << std::endl << std::endl;

	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
		{
			out << u[i*size_x + j] << " ";
			if (j == size_y - 1)
			{
				out << std::endl;
			}
		}

	out.close();
}


void calc_u(double *new_u, const double *u, const double tau, const double const_x, const double const_y, const int size_x, const int size_y)
{
	for (int i = 0; i < size_x*size_y; i++)
	{
		new_u[i] = 0.0;
	}

	for (int i = 1; i < size_x - 1; i++)
		for (int j = 1; j < size_y - 1; j++)
		{
			//new_u(i, j) = tau * koeff * ((u(i + 1, j) - 2 * u(i, j) + u(i - 1, j)) / (hx*hx) + (u(i, j + 1) - 2 * u(i, j) + u(i, j - 1)) / (hy * hy)) + u(i, j);
			
			new_u[i*size_x + j] = u[i*size_x + j] + const_x*tau*(u[(i + 1)*size_x + j] - 2 * u[i*size_x + j] + u[(i - 1)*size_x + j])
				+ const_y*tau*(u[i*size_x + j + 1] - 2 * u[i*size_x + j] + u[i*size_x + j - 1]);
		}
}