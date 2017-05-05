#include <stdio.h>
#include <pthread.h>

#define n_threads	10

void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

int main() {

	pthread_t thread_id[n_threads];
	int i, j;
	for (i = 0; i < n_threads; ++i)
		pthread_create( &thread_id[i], NULL, thread_function, NULL );
	
	for (j = 0; j < n_threads; ++j)
		pthread_join( thread_id[j], NULL );

	
	printf(" Finla counter value: %d \n", counter);
}

void *thread_function(void *dummyPtr)
{

	printf("Thread number %ld \n", pthread_self());
	pthread_mutex_lock( &mutex1 );
	counter++;
	pthread_mutex_unlock( &mutex1 );

}
