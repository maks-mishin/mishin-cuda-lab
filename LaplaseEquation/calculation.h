#pragma once

void solver_host(double *A, double *med, const int N)
{

	for (int i = 0; i < N*N; i++)
	{
		if ((i < N) || (i >= N*(N - 1)) || ((i % N) == 0) || (((i + 1) % N) == 0))
		{
			med[i] = A[i];
		}
		else
			med[i] = (A[i + 1] + A[i - 1] + A[i + N] + A[i - N]) / 4.0;
	}


}

void find_max(double *A, double *B, double *norma, const int N)
{
	for (int id = 0; id < N*N; id++)
	{
		if ((id < N) || (id >= N*(N - 1)) || ((id % N) == 0) || (((id + 1) % N) == 0))
		{
			norma[id] = 0.;
		}
		else
			norma[id] = fabs(B[id] - A[id]);
	}


}