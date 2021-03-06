#pragma once
#include "common.h"

// Size of array short int
const int byte_size = SIZE * sizeof(short);

//Array of structures
struct Pixel
{
	short int red;
	short int green;
	short int blue;
};

//Structure of arrays
struct Picture
{
	short int * red_arr;
	short int * green_arr;
	short int * blue_arr;
};

// Function init SOA
void init_SOA(Picture picture);

// Function init AOS
void init_AOS(Pixel *vec_pixels);

//Function print matrix with use pattern SOA
void print_matrix(Picture picture);

//Function print matrix with use pattern AOS
void print_matrix(Pixel *vec_pixels);

//Function filter picture on host with use SOA
void filter_SOA_host(Picture src_pict, Picture res_pict);

//Function filter picture on host with use AOS
void filter_AOS_host(Pixel *vec_pixels, Pixel *vec_pixels_res);

//__global__ void filter_SOA_device();
//__global__ void filter_AOS_device();

//Function for running program
void filter_img_test();

void free_SOA(Picture picture);
