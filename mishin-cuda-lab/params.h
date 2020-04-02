#pragma once
//file params.h

const int SIZE = 1048576; // Size of linear array
const int SIZE_M = 1024; // Width of matrix

						 //Params of kernel invoke
const int BLOCK_SIZE = 32; // Thread block size
const int BLOCKS = SIZE / BLOCK_SIZE + 1; // number of blocks
