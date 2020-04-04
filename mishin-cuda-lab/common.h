#pragma once
// Common params and functions

const int SIZE = 10; // Size of linear array
const int SIZE_M = 10; // Width of matrix

						 //Params of kernel invoke
const int BLOCK_SIZE = 32; // Thread block size
const int BLOCKS = SIZE / BLOCK_SIZE + 1; // number of blocks

//Make random number from min to max
template <class T>
T get_random_number(T min, T max)
{
	static const double fraction = 1.0 / (static_cast<T>(RAND_MAX) + 1.0);
	return static_cast<T>(rand() * fraction * (max - min + 1) + min);
}

