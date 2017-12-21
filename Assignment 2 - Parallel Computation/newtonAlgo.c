#include <stdio.h>
#include <math.h>

double newton(double x_0, double tol, int max_filters, int* iters_p, int* converged_p);
double f(double x);
double f_prime(double x);

int main(void) 
{

	double x_0; 
	double x;
	double tol;
	int max_iters;
	int iters;
	int converged;

	printf("Enter x_0, tol, and max_iters \n");
	scanf("%lf %lf %d", &x_0, &tol, &max_iters);

	printf("x_0 = %f, tol = %f, max_iters = %d \n", x_0, tol, max_iters);

	x = newton(x_0, tol, max_iters, &iters, &converged);
	
	if (converged) {
		
		printf("Method converged after %d iterations. \n", iters);
		printf("The approximate solution is %.15e \n", x);
		printf("f(%.15e) = %.15e \n", x, f(x));
	}
	else {
	
		printf("Method didn't converge after %d iterations. \n", iters);
		printf("The final estimate was %.15e \n", x);
		printf("f(%.15e) = %.15e \n", x, f(x));
	}
	
	return 0;
}


double newton(double x_0, double tol, int max_iters, int* iters_p, int* converged_p) {

	double x_new = x_0;
	double x_old;
	double divisor;
	int iter = 0;
	
	do {

		iter++;
		x_old = x_new;
		divisor = f_prime(x_old);
		if (divisor == 0.0)	{
		
			printf("f_prime = 0 \n");
			break;
		}		
	
		x_new = x_old - (f(x_old) / divisor);

	} while (fabs(x_new - x_old) > tol && iter < max_iters);			

	if (fabs(x_new - x_old) <= tol)
		*converged_p = 1;

	else
		*converged_p = 0;
	
	*iters_p = iter;

	return x_new;
}


double f(double x) {
	
	double y;
	// Could use other functions as well.	

	y = sin(x);
	return y;
}

double f_prime(double x) {

	double y;	
	y = cos(x);

	return y;

}






	
