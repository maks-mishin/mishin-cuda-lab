#pragma once

//Function print matrix
void print_matrix(float *Matrix);

//Function matrix multiplication on device
//__global__ void device_matMul( const float *A, const float *B, float *C);

//Function matrix multiplication on device with using shared memory
//__global__ void device_matMul_shared(const float* A, const float* B, float* C);

//Function matrix multiplication on host
void host_matMul(const float *A, const float *B, float *C);



