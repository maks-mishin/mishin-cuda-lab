#pragma once
#include <iostream>

/*
Function for solving value U on time step n+1
*/
void heat_step(double *U_n1, double *U_n, const double const_x, const double const_y, const int size_x, const int size_y);

//Function write to file
void write_file(double *U, std::string file_name, const int size_x, const int size_y);

//Function for make begin conditions and boundary conditions
void conditions(double *U_n, double *U_n1, const int size_x, const int size_y);

//Main function
void computing();