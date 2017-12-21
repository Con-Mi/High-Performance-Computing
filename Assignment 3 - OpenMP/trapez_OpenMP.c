// OpenMp for calculating a definite integral with 
// the trapezoidal rule.
// Integrating the function x^2.
// Static scheduling.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);
void Trapez(double a, double b, int n, double* integral_p);

int main(int argc, char* argv[])
{
	double integral; // Result of the integral
	double a, b; // Boundaries of the integral
	int n, thread_count;  // n Number of trapezoids

	if (argc != 2) 
		Usage(argv[0]);

	thread_count = strtol(argv[1], NULL, 10);

	printf("Enter a, b and n.(a and b for the boundaries.) \n");
	scanf("%lf %lf %d", &a, &b, &n);

	integral = 0.0;
	#pragma omp parallel num_threads(thread_count)
	Trapez(a, b, n, &integral);

	printf("With n = %d trapezoids, the estimate between %f and %f is: \n", n, a, b);
	printf("%.15e \n", integral);

	return 0;
}

void Usage(char* prog_name)
{
	fprintf(stderr, "Usage: %s <number of threads>\n", prog_name);
	exit(0);
}

double f(double x)
{
	double val = x*x;
	return val;
}

void Trapez(double a, double b, int n, double* integral_p)
{
	double h, x, my_integral;
	double local_a, local_b;
	int local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	h = (b-a)/n;
	local_n = n / thread_count;
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;
	my_integral = ( f(local_a) + f(local_b) ) / 2.0;
	for (int i = 0; i <= local_n - 1; ++i){
		x = local_a + i*h;
		my_integral += f(x);
	} 
	my_integral = my_integral*h;

	#pragma omp critical
	*integral_p += my_integral;
}