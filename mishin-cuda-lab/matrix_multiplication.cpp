//file matrix_multiplication.cpp

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include "common.h"
#include "matrix_multiplication.h"


//Function print matrix
void print_matrix(float *Matrix)
{
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << Matrix[i] << "\t";
		if ((i + 1) % 10 == 0)
			std::cout << std::endl;
	}
}

//Function matrix multiplication on device
/*__global__ void device_matMul(const float *A, const float *B, float *C)
{
	int glob_id = threadIdx.x + blockDim.x*blockIdx.x;
	if (glob_id < SIZE)
	{
		int i = glob_id % SIZE_M;
		int j = glob_id / SIZE_M;
		float temp = 0.0f;
		for (int k = 0; k < SIZE_M; k++)
		{
			temp += A[j*SIZE_M + k] * B[k*SIZE_M + i];
		}
		C[j*SIZE_M + i] = temp;
	}
}

//Function matrix multiplication on device with using shared memory
__global__ void device_matMul_shared(const float* A, const float* B, float* C)
{
	int glob_id = threadIdx.x + blockDim.x*blockIdx.x;
	if (glob_id < SIZE)
	{
		int i = glob_id % SIZE_M;
		int j = glob_id / SIZE_M;

		__shared__ float As[BLOCK_SIZE];
		float temp = 0.0f;
		for (int n = 0; n < SIZE_M / BLOCK_SIZE; n++)
		{
			As[threadIdx.x] = A[i*SIZE_M + n*BLOCK_SIZE + threadIdx.x];
			__syncthreads();

			for (int k = 0; k < BLOCK_SIZE; k++)
				temp += As[k] * B[(n * BLOCK_SIZE + k)*SIZE_M + j];
			//C[i*SIZE_M + j] += As[k] * B[(n * BLOCK_SIZE + k)*SIZE_M + j];
		}
		C[i*SIZE_M + j] = temp;
	}
}*/

//Function matrix multiplication on host
void host_matMul(const float *A, const float *B, float *C)
{
	for (int i = 0; i < SIZE_M; i++)
		for (int j = i; j < SIZE_M; j++)
			for (int k = 0; k < SIZE_M; k++)
			{
				C[i*SIZE_M + j] += A[i*SIZE_M + k] * B[k*SIZE_M + j];
			}
}
