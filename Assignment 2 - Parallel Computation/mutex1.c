#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n_threads	5

void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main() {

	int rc;
	pthread_t thread[n_threads];

	// Create independent threads each of which will execute functionC
	for (int ix = 0; ix < 5; ++ix){
		if( ( rc = pthread_create( &thread[ix], NULL, &functionC, NULL ) ) ) {

			printf("Thread creation failed: %d \n", rc);
	
		}
	}  

	/*if( ( rc2 = pthread_create( &thread2, NULL, &functionC, NULL ) ) ) {

		printf("Thread creation failed: %d \n", rc2);

	}*/

	// Wait till threads are complete before main continues. Unless we wait 
	// we run the risk of executiong an exit which will terminate the process
	// and all threads before the threads have completed.

	for (int ix = 0; ix < n_threads; ++ix){
		pthread_join( thread[ix], NULL );
	}
	
	exit(EXIT_SUCCESS);
	
	return 0;

}

void *functionC() {

	pthread_mutex_lock( &mutex1 );
	counter++;
	printf("Counter value: %d \n", counter);
	pthread_mutex_unlock( &mutex1 );

}


