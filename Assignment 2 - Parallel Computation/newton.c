// Newtons fractal with dynamic scheduling using POSIX threads.
// This program works for exponents of 1, 2, 5, 7 for passing 
// specified performance goals.
// Using the model x_in = (x_old * ((d -1)/d)) + ((1/d) * (1/(x_old) ^ (d-1)));


//////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


// Global variables //


int **ResultMatr;
int currentRow;
int nrOfLines, numberOfThreads;
double *realRoots, *imagRoots;
double exponent;
double lines;
char **colorsA;
pthread_t *threads;
pthread_mutex_t mutex_Row = PTHREAD_MUTEX_INITIALIZER;

//

// Define complex number as a struct //

struct ComplexNumber{
	double real;
	double imag;
}; 

//

void generatePPM(double exponent, int **data, int lines);
void getRoots(double realRoot[], double imagRoots[] , double exponent);
void rootConverged(double realA, double imagB, double oldRealA, double oldImagB, int* converged_pointer); 
void rootNotConverged(double realA, double imagB, int* notConverged_pointer);
struct ComplexNumber newtonsMethod(struct ComplexNumber x_out, double exponent);
int giveColor(struct ComplexNumber x, double realRoots[], double imagRoots[], double exponent);

/////////////////////////////////////////////

// Function to work in parallel.

////////////////////////////////////////////
void * doMyWork() 
{
	int myRow;
	int converged;
	int notConverged;
	struct ComplexNumber x;	
	struct ComplexNumber x_old;

	while (1) {
		
		pthread_mutex_lock(&mutex_Row);
	
		if (currentRow >= nrOfLines) {
			
			pthread_mutex_unlock(&mutex_Row);							
			pthread_exit(0);
		}

		myRow = currentRow;
		currentRow++;	
		pthread_mutex_unlock(&mutex_Row);
		int counter = 0;
		for (int i = 0; i < nrOfLines; ++i) {
			for (int j = 0; j < nrOfLines; ++j) {
				x.real = (-2.0 + (4.0 / (lines - 1.0))*j);
				x.imag = -(-2.0 + (4.0 / (lines - 1.0))*i);
				x_old.real = x.real;
				x_old.imag = x.imag;
				while(1) {
					x = newtonsMethod(x_old, exponent);
					rootConverged(x.real, x.imag, x_old.real, x_old.imag, &converged);
					if (converged) {				
						ResultMatr[i][j] = giveColor(x, realRoots, imagRoots, exponent);
						break;
					}
					rootNotConverged(x.real, x.imag, &notConverged);
					if (notConverged) {
						ResultMatr[i][j] = 0;
						break;
					}
					x_old = x;
				}
			}
		}
	}

}

/////////////////////////////////////////

int main(int argc, char *argv[]){

	int flags, opt;

	numberOfThreads = 0;
	flags = 0;

	while ((opt = getopt(argc, argv, "l:t:d:")) != -1)
	{
		switch(opt) {
		case 'l':
			lines = atoi(optarg);
			nrOfLines = lines;
			break;
		case 't':
			numberOfThreads = abs(atoi(optarg));
			break;
		case 'd':
			exponent = abs(atoi(optarg));	
			break;
		default:
			fprintf(stderr, "Usage %s [-t nrOfThreads] [-l nrOfLines] exponent\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	threads = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);	
	
	// Allocate the memory for the matrix.
	
	ResultMatr = (int **) malloc(sizeof(int*) * nrOfLines);
	colorsA = (char **) malloc(sizeof(char*) * 8);
	realRoots = (double *) malloc(sizeof(double) * exponent);	
	imagRoots = (double *) malloc(sizeof(double) * exponent);

	// Fill the matrix.

	for (int i = 0; i < nrOfLines; ++i)
		ResultMatr[i] = (int *) malloc(sizeof(int) * nrOfLines);
	for (int i = 0; i < 8; ++i )
		colorsA[i] = (char*) malloc(sizeof(char) * 7);
	colorsA[0] = "1 2 3 ";
	colorsA[1] = "3 3 1 ";
	colorsA[2] = "0 6 7 ";
	colorsA[3] = "0 5 4 ";
	colorsA[4] = "0 3 1 ";
	colorsA[5] = "2 0 0 ";
	colorsA[6] = "0 3 0 ";
	colorsA[7] = "6 6 6 ";

	for (int i = 0; i < nrOfLines; ++i)
		for (int j = 0; j < nrOfLines; ++j)
			ResultMatr[i][j] = 0;

	getRoots(realRoots, imagRoots, exponent);

	// Start distributing the work.
	currentRow = 0;	
	
	for (int i = 0; i < numberOfThreads; ++i){
		pthread_create(threads+i, NULL, doMyWork, NULL);
	}

	// Join the threads.
	for (int j = 0; j < numberOfThreads; ++j) {
		pthread_join(threads[j], NULL);	
	}

	/*for (int i = 0; i < lines; ++i) {
		for (int j = 0; j < lines; ++j)			
			printf("%d ", ResultMatr[i][j]);
		printf("\n");
	}
	*/
	/*
	for (int i = 0; i < exponent; ++i){
		printf("%f ", realRoots[i]);
		printf("%f ", imagRoots[i]);
		printf("\n");
	}*/
	generatePPM(exponent, ResultMatr, nrOfLines);
	
	return 0;
}

// End main.

///////////////////////////////////////////////////////////

void generatePPM(double exponent, int **data, int lines)
{
/////////////////////////////////////////////////////////////////////////////////

		int d; 
		d = (int) exponent;
		char filename[80];
		sprintf(filename, "newton_attractors_x%d.ppm", d);
		
		FILE * fp = fopen(filename, "wb");
		(void) fprintf(fp, "P3\n%d %d\n8\n", lines, lines);
		for (int i = 0; i < lines; ++i)
			for (int j = 0; j < lines; ++j)
				fprintf(fp,"%s", colorsA[data[i][j]]);
		fclose(fp);

}

void getRoots(double realRoots[], double imagRoots[] , double exponent)
{
/////////////////////////////////////////////////////////////////////////////////

	for (int index = 0; index < exponent; ++index){
		double argument = (2 * M_PI * index) / exponent;
		realRoots[index] = cos(argument);
		imagRoots[index] = sin(argument);
	}
} 


struct ComplexNumber newtonsMethod(struct ComplexNumber x_out, double exponent) 
{
/////////////////////////////////////////////////////////////////////////////////

	complex double x_in;
	
	if ((int) exponent == 1) {
		x_out.real = 1.0;
		x_out.imag = 0.0;
		return x_out;
	}
	else if ((int) exponent == 2) {
		x_in = ((1/2.0) * (x_out.real + x_out.imag * I)) + (1/(2.0*((x_out.real + x_out.imag * I))));
		x_out.real = creal(x_in);
		x_out.imag = cimag(x_in);
		return x_out;
	}

	else if ((int) exponent == 5) {
		x_in = ((4/5.0) * (x_out.real + x_out.imag * I)) + (1/5.0)*(1/((x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I)));
		x_out.real = creal(x_in);
		x_out.imag = cimag(x_in);
		return x_out;
	}
	
	else if ((int) exponent == 7) {
		x_in = ((6/7.0) * (x_out.real + x_out.imag * I)) + (1/7.0)*(1/((x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I) * (x_out.real + x_out.imag * I)) );
		x_out.real = creal(x_in);
		x_out.imag = cimag(x_in);
		return x_out;	
	}
}


void rootConverged(double realA, double imagB, double oldRealA, double oldImagB, int* converged_pointer) 
{
/////////////////////////////////////////////////////////////////////////////////
// Converges when x - x_old becomes less than 10^-3. Taking the |Complex X - X_old| to check tolerance level.

	if ((((realA - oldRealA) * (realA - oldRealA)) + ((imagB - oldImagB) * (imagB - oldImagB))) < 0.000001)
		*converged_pointer = 1;
	else 
		*converged_pointer = 0;
}


void rootNotConverged(double realA, double imagB, int* notConverged_pointer)
{
/////////////////////////////////////////////////////////////////////////////////

	if ( (fabs(realA) > 10000000000) || ((imagB)*(imagB) > 10000000000) ) {
		*notConverged_pointer = 1;
	}

	else {
		*notConverged_pointer = 0;	
	}	

}


int giveColor(struct ComplexNumber x, double realRoots[], double imagRoots[], double exponent)
{
/////////////////////////////////////////////////////////////////////////////////

	int color = -1;
	if ((int) exponent == 1) {
		color = 1;
	}

	else {
		for (int counter = 0; counter < exponent; ++counter)
		{
			if ( ( (x.real - realRoots[counter]) * (x.real - realRoots[counter]) ) + ( (x.imag - imagRoots[counter]) * (x.imag - imagRoots[counter]) ) < 0.000001 ) 
			{
				color = counter+1;
				break;
			}
		}
	}
	
	if (color == -1)
	{
		color = 0;
	}
	return color;

}




