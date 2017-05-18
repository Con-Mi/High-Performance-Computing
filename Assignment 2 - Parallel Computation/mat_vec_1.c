// Matrix - vector multiplication with pthreads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables 
int thread_count;
int m, n;
double* A;
double* x;
double* y;

// Serial functions

void Usage(char* prog_name);
void Read_matrix(char* prompt, double A[], int m, int n);
void Read_vector(char* prompt, double x[], int n);
void Print_matrix(char* ttle, double A[], int m, int n);
void Print_vector(char* ttle, double y[], int m);

// Parallel function

void *Pth_mat_vect(void* rank);

int main(int argc, char* argv[]) {

	long	thread;
	pthread_t* thread_handles;

	if (argc != 2) Usage(argv[0]);
	thread_count  = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count*sizeof(pthread_t));

	printf("Enter m and n\n");
	scanf("%d%d", &m, &n);

	A = malloc(m*n*sizeof(double));
	x = malloc(n*sizeof(double));
	y = malloc(m*sizeof(double));

	Read_matrix("Enter the matrix", A, m, n);
	
	Read_vector("Enter the vector", x, n);

	for (thread = 0; thread < thread_count; ++thread)
		pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*) thread);

	for (thread = 0; thread < thread_count; ++thread)
		pthread_join(thread_handles[thread], NULL);

	Print_vector("The product is", y, m);

	free(A);
	free(x);
	free(y);
	free(thread_handles);
	return 0;

}


void Usage (char* prog_name) {

	fprintf(stderr, "Usage: %s <thread_count> \n", prog_name);
	exit(0);
}


void Read_matrix(char* prompt, double A[], int m, int n)
{

	int	i, j;

	printf("%s \n", prompt);
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			scanf("%lf", &A[i*n+j]);


}

void Read_vector(char* prompt, double x[], int n) {

	int i;
	

	printf("%s \n", prompt);
	for (i = 0; i  < n; ++i)
		scanf("%lf", &x[i]);

}

void *Pth_mat_vect(void* rank)
{

	long my_rank = (long) rank;
	int i, j;
	int local_m = m / thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = my_first_row + local_m - 1;

	for ( i = my_first_row; i <= my_last_row; ++i) {
		y[i] = 0.0;
		for (j = 0; j < n; ++j)
			y[i] += A[i*n + j] * x[j];
	}

	return NULL;

}


void Print_matrix( char* title, double A[], int m, int n) {
   int   i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
         printf("%4.1f ", A[i*n + j]);
      printf("\n");
   }
}  /* Print_matrix */


/*------------------------------------------------------------------
 * Function:    Print_vector
 * Purpose:     Print a vector
 * In args:     title, y, m
 */
void Print_vector(char* title, double y[], int m) {
   int   i;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
      printf("%4.1f ", y[i]);
   printf("\n");
}  /* Print_vector */
























