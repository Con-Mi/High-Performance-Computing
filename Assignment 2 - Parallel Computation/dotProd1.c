#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ix_m	1000

double a[ix_m], b[ix_m], sum;  // Global variables???

#define n_threads	4

pthread_mutex_t mutex_sum;

// assuming that ix_m is divisible by n_threads
#define block_size (ix_m / n_threads)

void* dotProd(void* arg);

int main() {

	int ret;
	size_t ix, tx;
	pthread_t threads[n_threads];

	for (ix = 0; ix < ix_m; ++ix)
		a[ix] = b[ix] = 1;
	sum = 0;

	// thread creation and joining
	
	// thread creation
	pthread_mutex_init(&mutex_sum, NULL);
	
	for(tx = 0, ix = 0; tx < n_threads; ++tx, ix += block_size) {
	
		double ** arg = malloc(2*sizeof(double*));
		arg[0] = a+ix; arg[1] = b+ix;
	
		if (ret = pthread_create(threads[tx], NULL, dotProd, (void*)arg)) {

			printf("Error creating thread: %d \n", ret);
			exit(1);

		}
	
	}

	// thread joining	
	
	for (tx = 0; tx < n_threads; ++tx) {

		if (ret = pthread_join(threads[tx], NULL)){

			printf("Error joining thread: %d \n", ret);
			exit(1);

		}	

	}
	pthread_mutex_destroy(&mutex_sum);

	printf("sum = %f \n", sum);

	return 0;
}
	 
