#pragma once
//file matrix_multiplication.h

//Function print matrix
void print_matrix(const float *Matrix);

//Make random number from min to max
float get_random_number(int min, int max);

//Function matrix multiplication on device
//__global__ void device_matMul( const float *A, const float *B, float *C);

//Function matrix multiplication on device with using shared memory
//__global__ void device_matMul_shared(const float* A, const float* B, float* C);

//Function matrix multiplication on host
void host_matMul(const float *A, const float *B, float *C);



