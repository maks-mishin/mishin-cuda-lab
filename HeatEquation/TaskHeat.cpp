#include <fstream>
#include "TaskHeat.h"

//#define u(i, j) u[(i)*n + (j)]
//#define new_u(i, j) new_u[(i)*n + (j)]

TaskHeat::TaskHeat(double _execution_time)
{
	execution_time = _execution_time;
	grid = GridHeat(1.0, 1.0, 0.1, 0.1);
	setInitConditions();
}

TaskHeat::~TaskHeat()
{
}

void TaskHeat::setInitConditions()
{
	n = grid.steps_x;
	m = grid.steps_y;

	u = new double[n*m];
	new_u = new double[n*m];

	u_d = new double[n*m];
	new_u_d = new double[n*m];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			u[i*n + j] = 0.0;

			if (grid.grid_x[i] == 0.5 && grid.grid_y[j] == 0.5)
			{
				u[i*n + j] = 1.0;
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

	dt = grid.dx * grid.dy;

	double time = 0.0;
	do
	{
		if (execution_time - time < dt)
			dt = execution_time - time;

		calc_u(new_u, u, dt, grid.dx, grid.dy, 1/grid.dx*grid.dx, 1/grid.dy*grid.dy, n, m);
		
		tmp = u;
		u = new_u;
		new_u = tmp;

		time += dt;
		
	} while (time < execution_time);
}

void TaskHeat::writeValues(/*double time*/)
{
	std::ofstream out;

	out.open("U.txt");

	//out << "time :" << time << std::endl << std::endl;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			out << u[i*n + j] << " ";
			if (j == m - 1)
			{
				out << std::endl;
			}
		}

	out.close();
}


void calc_u(double *new_u, const double *u, const double tau, const double hx, const double hy, const double const_x, const double const_y, const int size_x, const int size_y)
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