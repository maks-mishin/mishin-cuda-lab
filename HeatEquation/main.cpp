#include "GridHeat.h"
#include "TaskHeat.h"
#include <time.h>
#include <iostream>

int main()
{
	double start_execution_time = 0.0;
	double end_execution_time = 0.0;

	TaskHeat taskHost(10.0);

	start_execution_time = clock();

	taskHost.compute_on_host();
	
	end_execution_time = clock();

	taskHost.write_values();

	
	std::cout << "Execution time on Host = " << (double)(end_execution_time - start_execution_time)/CLOCKS_PER_SEC << std::endl;

	return 0;
}