#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <fstream>

/*
Function for solving value U on time step n+1
*/
void heat_step(double *U_n1, double *U_n, const double const_x, const double const_y, const int size_x, const int size_y)
{
	for (int i = 1; i < size_x - 1; i++)
	{
		for (int j = 1; j < size_y - 1; j++)
		{
			U_n1[i*size_x + j] = U_n[i*size_x + j] + const_x*(U_n[(i + 1)*size_x + j] - 2 * U_n[i*size_x + j] + U_n[(i - 1)*size_x + j])
				+ const_y*(U_n[i*size_x + j + 1] - 2 * U_n[i*size_x + j] + U_n[i*size_x + j - 1]);
		}
	}
}

//Function write to file
void write_file(double *U, std::string file_name, const int size_x, const int size_y)
{
	std::ofstream out;
	out.open(file_name);
	if (out.is_open())
	{
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				out << U[i*size_x + j] << "  ";
			}
			out << std::endl;
		}
	}
	else
		std::cout << "File " << file_name << " could not open." << std::endl;
}

//Function for make begin conditions and boundary conditions
void conditions(double *U_n, double *U_n1, const int size_x, const int size_y)
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			// Begin conditions
			if (i == j && i == size_x / 2)
				U_n[i*size_x + j] = 1;
			else
				U_n[i*size_x + j] = 0;

			// Boundary conditions
			U_n1[i*size_x + j] = 0;
		}
	}
}

//Main function
void computing()
{
	const double c = 0.1;
	const double time_max = 10;

	const int size_x = 10, size_y = 10;

	const double dx = 1.0 / size_x - 1; // step on x
	const double dy = 1.0 / size_y - 1; // step on y

	double t = 0, dt = dx*dy; // time, step on time
	double time_work = 0;

	const double c_x = c*dt / (dx*dx);
	const double c_y = c*dt / (dy*dy);

	double *U_n = nullptr, *U_n1 = nullptr, *tmp = nullptr;

	U_n = new double[size_x*size_y];
	U_n1 = new double[size_x*size_y];

	conditions(U_n, U_n1, size_x, size_y);


	clock_t start_host = clock();
	do
	{
		if (time_max - t < dt)
			dt = time_max - t;

		heat_step(U_n1, U_n, c_x, c_y, size_x, size_y);

		tmp = U_n;
		U_n = U_n1;
		U_n1 = tmp;

		t += dt;
	} while (t < time_max);
	clock_t finish_host = clock();

	time_work = (double)(finish_host - start_host) / CLOCKS_PER_SEC;

	std::cout << "Time host: " << time_work << std::endl;
	write_file(U_n1, "result.txt", size_x, size_y);
}