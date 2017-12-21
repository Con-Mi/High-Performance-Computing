#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Parallel implementation of approximating PI with OpenMp.
// Integrate 1 / (1 + x^2) from 0 to inf. 

void main()
{
	static long num_steps = 100;
	double step;
	double x, pi, sum = 0.0;
	
	step = 1.0 / (double) num_steps;
	

	//omp_set_dynamic(1);
	//#pragma set_num_threads(100);
	//#pragma omp parallel for reduction(+:sum) num_threads(10)
	#pragma omp parallel for reduction(+:sum) num_threads(100) 
		for (int i = 0; i < num_steps; ++i) 
		{
			//x = (i + 0.5) * step;
			//sum += 4.0/(1.0+x*x);
			sum += i;
		}
	
	

	pi = step*sum;
	
	printf("%f \n", pi);
}


/* Results. On a machine with 4 cores.
With OpenMp (code above) : Result = 3.155794, Time = 12.49 sec
With regular for loop    : Result = 3.141593,
*/
