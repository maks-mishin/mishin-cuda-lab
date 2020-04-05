#pragma once

//Calculation step on host
void heat_step_host(double *U_n1, const double *U_n, const double dt, const double const_x, const double const_y, const int size_x, const int size_y)
{
	for (int i = 1; i < size_x - 1; i++)
		for (int j = 1; j < size_y - 1; j++)
		{
			U_n1[i*size_x + j] = U_n[i*size_x + j] + const_x*dt*(U_n[(i + 1)*size_x + j] - 2 * U_n[i*size_x + j] + U_n[(i - 1)*size_x + j])
				+ const_y*dt*(U_n[i*size_x + j + 1] - 2 * U_n[i*size_x + j] + U_n[i*size_x + j - 1]);
		}
}