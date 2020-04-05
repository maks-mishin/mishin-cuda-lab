#include "TaksLaplase.h"
#include <fstream>


TaksLaplase::TaksLaplase(double _a, double _b, double _dx, double _dy)
{
	grid = GridHeat(_a, _b, _dx, _dy);
}


TaksLaplase::~TaksLaplase()
{
}

void TaksLaplase::write_values()
{
	std::ofstream out;

	out.open("values.txt");

	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
		{
			out << U_n[i*size_x + j] << " ";
			if (j == size_y - 1)
			{
				out << std::endl;
			}
		}

	out.close();
}