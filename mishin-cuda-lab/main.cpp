#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "filter_img.h"
#include "matrix_multiplication.h"


//Main function
int main()
{
	//init timer
	srand(static_cast<unsigned int>(time(0)));

	Picture picture_src, picture_res;
	Pixel *vec_pixels_src, *vec_pixels_res;

	double start_SOA, end_SOA,
		start_AOS, end_AOS;

	// allocate memory on host
	picture_src.red_arr = (short*)malloc(byte_size);
	picture_src.green_arr = (short*)malloc(byte_size);
	picture_src.blue_arr = (short*)malloc(byte_size);

	picture_res.red_arr = (short*)malloc(byte_size);
	picture_res.green_arr = (short*)malloc(byte_size);
	picture_res.blue_arr = (short*)malloc(byte_size);

	vec_pixels_src = (Pixel*)malloc(byte_size * 3);
	vec_pixels_res = (Pixel*)malloc(byte_size * 3);


	// init picture on host
	init_SOA(picture_src);
	init_AOS(vec_pixels_src);


	start_SOA = clock();
	for (size_t i = 0; i < 100; i++)
	{
		filter_SOA_host(picture_src, picture_res);
	}
	end_SOA = clock();

	start_AOS = clock();
	for (size_t i = 0; i < 100; i++)
	{
		filter_AOS_host(vec_pixels_src, vec_pixels_res);
	}
	end_AOS = clock();

	std::cout << "Average time with using SOA: " << (end_SOA - start_SOA) / CLOCKS_PER_SEC / 10 << std::endl;
	std::cout << "\nAverage time with using AOS: " << (end_AOS - start_AOS) / CLOCKS_PER_SEC / 10 << std::endl;

	free_SOA(picture_src);

	return 0;
}
