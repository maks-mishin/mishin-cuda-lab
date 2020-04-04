#include "GridHeat.h"
#include "TaskHeat.h"
#include <omp.h>
#include <time.h>


int main()
{
	double start_execution_time = 0.0;
	double end_execution_time = 0.0;

	//TaskHeat taskDevice(10.0);
	TaskHeat taskHost(10.0);
	
	//////Device
	//start_execution_time = omp_get_wtime();

	//taskDevice.compute_on_device();

	//end_execution_time = omp_get_wtime();

	//printf("Execution time on Device = %lf \n", end_execution_time - start_execution_time);
	
	//////Host
	//start_execution_time = omp_get_wtime();

	start_execution_time = clock();

	//taskHost.writeValues();
	taskHost.compute_on_host();

	//end_execution_time = omp_get_wtime();
	end_execution_time = clock();

	taskHost.writeValues();

	printf("Execution time on Host = %lf \n", (double)(end_execution_time - start_execution_time)/CLOCKS_PER_SEC);

	return 0;
}