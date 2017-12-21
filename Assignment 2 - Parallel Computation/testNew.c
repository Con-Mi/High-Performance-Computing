// Test my newton method if it produces correct results.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

struct ComplexNumber{
	double real;
	double imag;
};



int main() {

	complex double x;
	x = -2 - 2*I;

	struct ComplexNumber x_out;
	complex double x_in;
	x_out.real = creal(x);
	x_out.imag = cimag(x);

	for (int i = 0; i < 100; ++i)
	{
		x_in = ((6/7.0) * (x_out.real + x_out.imag * I)) + (1/7.0)*(1/((x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I)) );
		x_out.real = creal(x_in);
		x_out.imag = cimag(x_in);
		printf("%f + %f i \n", creal(x_in), cimag(x_in));

	}

	return 0;


	// Ok this works but further investigation is needed.
	// Try with more things and check what is wrong.

}

// struct ComplexNumber newtonsMethod()
// {


// }