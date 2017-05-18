// Matrix - Matrix multiplication with mutex
// Dynamic scheduling of the multiplication using low level posix threads.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables

int row1; // Size of columns of matrix 1.
int col1; // SIze of rows of matrix 1.
int row2, col2, currentRow, **InMat1, **InMat2, **ResMat;
int numberOfThreads;

pthread_t * threads;

// Mutex for current row.
pthread_mutex_t mutex_Row = PTHREAD_MUTEX_INITIALIZER;


void * doMyWork(int thread_id) 
{

	 
	// With while(1) we can unconditionally block a device
	// until an accredited operator manually reboots it.
	
	int i, j, myRow;	
	
	while(1) {

		printf("\n %d: Locking ... ", thread_id);
		
		pthread_mutex_lock(&mutex_Row);
		
		if (currentRow >= row1) {
			
			pthread_mutex_unlock(&mutex_Row);
			printf("\n %d: Unlocking... \n I am Thread No.: %d. I have no work to do.", thread_id, thread_id);
	
			if (thread_id == 0)
				return;

			pthread_exit(0);
		}
		
		myRow = currentRow;
		currentRow++;
		printf("\n I am Thread No.: %d. I have work to do.", thread_id);
		pthread_mutex_unlock(&mutex_Row);
		printf("\n %d: unlocking... Operating on Row: %d.\n", thread_id, myRow);

		for (j = 0; j < col2; ++j)
			for (i = 0; i < col1; ++i)
				ResMat[myRow][j] += InMat1[myRow][i] * InMat2[i][j];

	}
}



int main(int argc, char *argv[])
{

	int i, j;
	if (argc < 6){
		printf("\n Insufficient arguments. \n Usage:");
		printf("./a.out row1 col1 row2 col2 thread. \n");
	}

	row1 = abs(atoi(argv[1]));
	col1 = abs(atoi(argv[2]));
	row2 = abs(atoi(argv[3]));
	col2 = abs(atoi(argv[4]));

	if (col1 != row2){

		printf("Cannot multiply matrices of given type. Aborting \n");	
		exit(0);
	}

	numberOfThreads = abs(atoi(argv[5]));

	printf("Row1: %d. Col1: %d, Row2: %d,  Col2: %d. Number of Threads: %d. \n", row1, col1, row2, col2, numberOfThreads);

	InMat1 = (int **) malloc(sizeof(int *) * row1);
	for (i = 0; i < row1; ++i)
		InMat1[i] = (int *) malloc(sizeof(int) * col1);

	InMat2 = (int **) malloc(sizeof(int *) * row2);
	for (i = 0; i < row2; ++i)
		InMat2[i] = (int *) malloc(sizeof(int) * col2);

	// Allocate the memory for the output matrix.
	ResMat = (int **) malloc(sizeof(int *) * row1);
	for (i = 0; i < row1; ++i)
		ResMat[i] = (int *) malloc(sizeof(int) * col2);

	//Populate the matrices.

	for (i = 0; i < row1; ++i)
		for (j = 0; j < col1; ++j)
			InMat1[i][j] = 1;

	for (i = 0; i < row2; ++i)
		for (j = 0; j < col2; ++j)
			InMat2[i][j] = 2;

	for (i = 0; i < row1; ++i)
		for (j = 0; j < col2; ++j)
			ResMat[i][j] = 0;	

	threads = (pthread_t *) malloc(sizeof(pthread_t) * numberOfThreads);

	// Start distributing the work. The problem is super parallel so its easy for us.
	// Every time a new thread starts it checks if the row is occupied, and moves on.
	currentRow = 0;
	
	for (i = 0; i < numberOfThreads; ++i){
		pthread_create(&threads[i], NULL, (void *(*) (void *)) doMyWork, (void *) (i + 1));
		printf("Thread %d created. \n", i+1);
	}

	for (i = 0; i < numberOfThreads; ++i){
		printf("Joning Thread %d \n", i+1);
		pthread_join(threads[i], NULL);
		printf("Thread %d joined \n", i + 1);
		printf("\n");
	}
	
	for (i  = 0; i < row1; ++i) {
		for (j =  0; j < col2; ++j)
			printf("%d ", ResMat[i][j]);		
		printf("\n");
	}	
		
	printf("Program is Done \n");
	
	return 0;

}


