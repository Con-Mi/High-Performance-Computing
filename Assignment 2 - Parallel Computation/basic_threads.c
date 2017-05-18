// Basic Threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global Variable to access all threads
int thread_count;

void Usage(char* prog_name);
void *Hello(void* rank); // Thread function

int main(int argc, char* argv[]) {

	long	thread;
	pthread_t* thread_handles;

	// Get number of threads from command line
	if (argc != 2) Usage(argv[0]);
	thread_count = strtol(argv[1], NULL, 10);
	if (thread_count <= 0) Usage(argv[0]);

	thread_handles = malloc(thread_count*sizeof(pthread_t)); //Multiplication inside the parenthesis.

	for (thread = 0; thread < thread_count; ++thread)
		pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);

	printf("Hello from the main thread \n");

	for (thread = 0; thread < thread_count; ++thread)
		pthread_join(thread_handles[thread], NULL);

	free(thread_handles);
	return 0;
}

void *Hello(void* rank) {

	long my_rank = (long) rank; 
	
	printf("Hello from thread %ld of %d \n", my_rank, thread_count);
		
	return NULL;
}

void Usage(char* prog_name) {

	fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
	fprintf(stderr, "number of threads > 0 \n");
	exit(0);

}
