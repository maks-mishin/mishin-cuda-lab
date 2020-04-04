/*
file filter_img.cpp
* Program for processing of images by the example of a matrix
* @author - Mishin M.A.
* @data - 13.03.2020
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "common.h"
#include "filter_img.h"

// Function init SOA
void init_SOA(Picture picture)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		picture.red_arr[i] = get_random_number(0, 255);
		picture.green_arr[i] = get_random_number(0, 255);
		picture.blue_arr[i] = get_random_number(0, 255);
	}
}

// Function init AOS
void init_AOS(Pixel *vec_pixels)
{
	Pixel temp;
	for (size_t i = 0; i < SIZE; i++)
	{
		temp.red = get_random_number(0, 255);
		temp.green = get_random_number(0, 255);
		temp.blue = get_random_number(0, 255);
		vec_pixels[i] = temp;
	}
}



//Function print matrix with use pattern SOA
void print_matrix(Picture picture)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		std::cout << "(" << picture.red_arr[i] << ", " << picture.blue_arr[i] << ", " << picture.blue_arr[i] << ")" << "\t";
		if ((i + 1) % 10 == 0)
			std::cout << std::endl;
	}
}

//Function print matrix with use pattern AOS
void print_matrix(Pixel *vec_pixels)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		std::cout << "(" << vec_pixels[i].red << ", " << vec_pixels[i].green << ", " << vec_pixels[i].blue << ")" << "\t";
		if ((i + 1) % 10 == 0)
			std::cout << std::endl;
	}
}


//Function filter picture on host with use SOA
void filter_SOA_host(Picture src_pict, Picture res_pict)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		if (i < SIZE_M || i >(SIZE - SIZE_M) || (i + 1) % 10 == 0 || i % 10 == 0)
		{
			continue;
		}
		else
		{
			res_pict.red_arr[i] = (1.0 / 9)*(src_pict.red_arr[i] + src_pict.red_arr[i + 1] + src_pict.red_arr[i - 1] +
				src_pict.red_arr[i + SIZE_M] + src_pict.red_arr[i + 1 + SIZE_M] + src_pict.red_arr[i - 1 + SIZE_M] +
				src_pict.red_arr[i - SIZE_M] + src_pict.red_arr[i + 1 - SIZE_M] + src_pict.red_arr[i - 1 - SIZE_M]);

			res_pict.green_arr[i] = (1.0 / 9)*(src_pict.green_arr[i] + src_pict.green_arr[i + 1] + src_pict.green_arr[i - 1] +
				src_pict.green_arr[i + SIZE_M] + src_pict.green_arr[i + 1 + SIZE_M] + src_pict.green_arr[i - 1 + SIZE_M] +
				src_pict.green_arr[i - SIZE_M] + src_pict.green_arr[i + 1 - SIZE_M] + src_pict.green_arr[i - 1 - SIZE_M]);

			res_pict.blue_arr[i] = (1.0 / 9)*(src_pict.blue_arr[i] + src_pict.blue_arr[i + 1] + src_pict.blue_arr[i - 1] +
				src_pict.blue_arr[i + SIZE_M] + src_pict.blue_arr[i + 1 + SIZE_M] + src_pict.blue_arr[i - 1 + SIZE_M] +
				src_pict.blue_arr[i - SIZE_M] + src_pict.blue_arr[i + 1 - SIZE_M] + src_pict.blue_arr[i - 1 - SIZE_M]);
		}
	}
}

//Function filter picture on host with use AOS
void filter_AOS_host(Pixel *vec_pixels, Pixel *vec_pixels_res)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		if (i < SIZE_M || i >(SIZE - SIZE_M) || (i + 1) % 10 == 0 || i % 10 == 0)
		{
			continue;
		}
		else
		{
			vec_pixels_res[i].red = (1.0 / 9)*(vec_pixels[i].red + vec_pixels[i + 1].red + vec_pixels[i - 1].red +
				vec_pixels[i + SIZE_M].red + vec_pixels[i + 1 + SIZE_M].red + vec_pixels[i - 1 + SIZE_M].red +
				vec_pixels[i - SIZE_M].red + vec_pixels[i + 1 - SIZE_M].red + vec_pixels[i - 1 - SIZE_M].red);

			vec_pixels_res[i].green = (1.0 / 9)*(vec_pixels[i].green + vec_pixels[i + 1].green + vec_pixels[i - 1].green +
				vec_pixels[i + SIZE_M].green + vec_pixels[i + 1 + SIZE_M].green + vec_pixels[i - 1 + SIZE_M].green +
				vec_pixels[i - SIZE_M].green + vec_pixels[i + 1 - SIZE_M].green + vec_pixels[i - 1 - SIZE_M].green);

			vec_pixels_res[i].blue = (1.0 / 9)*(vec_pixels[i].blue + vec_pixels[i + 1].blue + vec_pixels[i - 1].blue +
				vec_pixels[i + SIZE_M].blue + vec_pixels[i + 1 + SIZE_M].blue + vec_pixels[i - 1 + SIZE_M].blue +
				vec_pixels[i - SIZE_M].blue + vec_pixels[i + 1 - SIZE_M].blue + vec_pixels[i - 1 - SIZE_M].blue);
		}
	}
}

void free_SOA(Picture picture)
{
	free(picture.red_arr);
	free(picture.green_arr);
	free(picture.blue_arr);
}

void filter_img_test()
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
}