#include <stdio.h>
#include <time.h>

void 
mul_cpx(double *, double *, double *, double *, double *, double *); //declaration of the function. 


void mul_cpx1( double * a_re, double * a_im, double * b_re, double * b_im, double * c_re, double * c_im)
{	
	 	
	*a_re = *b_re * *c_re - *b_im * *c_im; 
	*a_im = *b_re * *c_im + *b_im * *c_re;
}

void main() {
	
	clock_t begin = clock();

	double a_real[30000]; // Pointers
	double a_imag[30000];
	double b_real[30000];
	double b_imag[30000];
	double c_real[30000];
	double c_imag[30000];

	for (size_t i = 0; i < 30000; i++) {
		b_real[i] = i;
		b_imag[i] = i;
		c_real[i] = i;
		c_imag[i] = i;
	}

	for (size_t i = 0; i < 30000; i++) {
		mul_cpx(a_real+i, a_imag+i, b_real+i, b_imag+i, c_real+i, c_imag+i);	
	}

	/* 
	for (size_t i = 0; i < 30000; i++) {
		a_real[i] = b_real[i] * c_real[i] - b_imag[i] * c_imag[i];
		a_imag[i] = b_real[i] * c_imag[i] - b_imag[i] * c_real[i];	
	}
	*/

	
	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\n Time spent by In is: %f secs \n", time_spent);
	//mul_cpx(&a_real, &a_imag, &b_real, &b_imag, &c_real, &c_imag);
	//printf("\n Real part of a equals %f, Imaginary part equals %f \n", a_real, a_imag);
}
