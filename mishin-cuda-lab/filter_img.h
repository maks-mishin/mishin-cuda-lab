#pragma once
// file filter_img.h
#include <vector>


// Size of array short int
const int byte_size = SIZE * sizeof(short);

//Array of structures, array - vector<Pixel>
struct Pixel;

//Structure of arrays
struct Picture;

// Function init AOS
void init_AOS(std::vector<Pixel> &arr_pixels);

//Function print matrix with use pattern SOA
void print_matrix(Picture &picture);

//Function print matrix with use pattern AOS
void print_matrix(std::vector<Pixel> &vec_pixels);

//Function filter picture on host with use SOA
void filter_SOA_host(Picture& src_pict, Picture& res_pict);

//Function filter picture on host with use AOS
void filter_AOS_host(std::vector<Pixel> &vec_pixels, std::vector<Pixel> &vec_pixels_res);

//__global__ void filter_SOA_device();
//__global__ void filter_AOS_device();


void free_SOA(Picture &picture);
