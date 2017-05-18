// Newtons fractal with dynamic scheduling of POSIX threads.
// This program works for exponents of 1, 2, 5, 7 for reaching 
// specified performance goals.

#include <pthread.h>
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


// Global variables

complex double **ComplexMatr, **ResultMatr;
int currentRow;
int nrOfLines, numberOfThreads;
double exponent;

pthread_t *threads;
pthread_mutex_t mutex_Row = PTHREAD_MUTEX_INITIALIZER;



void * doNewtonsWork() 
{
	int myRow;
	
	while (1) {
		
		pthread_mutex_lock(&mutex_Row);
	
		if (currentRow >= nrOfLines) {
			
			pthread_mutex_unlock(&mutex_Row);
			//printf("Unlocking... I am thread No.: %d. I have no work \n", threadId);
			//if (threadId == 0)
			//	return;							
			pthread_exit(0);
		}

		myRow = currentRow;
		currentRow++;
		//printf("I am thread No.: %d. I have work to do. \n", threadId);	
		pthread_mutex_unlock(&mutex_Row);
		//printf("Unlocking.. Operating on Row: %d. \n", myRow);
		if (exponent == 1) {
	
			for (int i = 0; i < nrOfLines; ++i)
				for (int j = 0; j < nrOfLines; ++j)
					ResultMatr[i][j] += (1/exponent);
					
		}
		else if (exponent == 2) {
			for (int i = 0; i < nrOfLines; ++i)
				for (int j = 0; j < nrOfLines; ++j)
					ResultMatr[i][j] += (1/exponent);
			
		}
		else if (exponent == 5) {
		
			xsquared = ((creal() * creal()) - (cimag() * cimag)) + (2 * cimag() * creal());
		}
		else if (exponent == 7) {

			xsquared = ((creal() * creal()) - (cimag() * cimag)) + (2 * cimag() * creal());
		}
	}

}



int main(int argc, char *argv[]){

	int flags, opt;
	double lines;

	numberOfThreads = 0;
	flags = 0;

	while ((opt = getopt(argc, argv, "l:t:d:")) != -1) {
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
	
	
	printf("Number of threads to be used: %d, Number of rows and columns of(square) Matrix: %d x %d , Exponent: %f \n", numberOfThreads, nrOfLines, nrOfLines, exponent);
	threads = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);	// Error here.
	
	// Allocate the memory for the matrices	
	
	ComplexMatr = (complex double **) malloc(sizeof(complex double*) * nrOfLines);
	
	for (int i = 0; i < nrOfLines; ++i) 
		ComplexMatr[i] = (complex double *) malloc(sizeof(complex double) * nrOfLines);

	ResultMatr = (complex double **) malloc(sizeof(complex double *) * nrOfLines);
	
	for (int i = 0; i < nrOfLines; ++i)
		ResultMatr[i] = (complex double *) malloc(sizeof(complex double) * nrOfLines);

	// Fill the matrices.
	for (int i = 0; i < nrOfLines; ++i)	
		for (int j = 0; j < nrOfLines; ++j)
			ComplexMatr[i][j] = ((-2.0 + (4.0 / (lines - 1.0))*j) + ((-2.0 + (4.0 / (lines - 1.0))*i) * I));	

	for (int i = 0; i < nrOfLines; ++i)
		for (int j = 0; j < nrOfLines; ++j)
			ResultMatr[i][j] = 0.0 + 0.0*I;

	// Start distributing the work.
	
	currentRow = 0;	


	for (int i = 0; i < numberOfThreads; ++i){
		pthread_create(threads+i, NULL, doNewtonsWork, NULL);
		//printf("Thread %d created \n", i + 1);
	}

	// Join the threads.
	for (int j = 0; j < numberOfThreads; ++j) {
		printf("Joining thread %d... \n", j+1);
		pthread_join(threads[j], NULL);	
		printf("Thread %d has just joined \n", j+1);
	}
	// Print the Matrix

	for (int i = 0; i < nrOfLines; ++i){
		for (int j = 0; j < nrOfLines; ++j)
			printf("%f+%fi ", creal(ResultMatr[i][j]), cimag(ResultMatr[i][j]));
		printf("\n");
	} 
	return 0;
}


