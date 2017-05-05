#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex	= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var	= PTHREAD_COND_INITIALIZER;

void *functionCount1();
void *functionCount2();
int count = 0;

#define COUNT_DONE	10
#define COUNT_HALT1	3
#define COUNT_HALT2	6

int main()
{

	pthread_t thread1, thread2;
	
	pthread_create( &thread1, NULL, &functionCount1, NULL );
	pthread_create( &thread2, NULL, &functionCount2, NULL );

	pthread_join( thread1, NULL );
	pthread_join( thread2, NULL );

	printf("Final Count: %d \n", count);

}

// Write numbers 1 - 3 and 8 - 10 as permitted by functionCount2()

void *functionCount1()
{

	for (;;)
	{

		//Lock mutex and then wait for signal to release mutex
		pthread_mutex_lock( &count_mutex );
		

		// Wait while functionCount2() operates on count
		// mutex unlocked if condition variable in functionCount2() signaled.

		pthread_cond_wait( &condition_var, &count_mutex );
		count++;
		printf("Counter Value functionCount1: %d \n", count);

		pthread_mutex_unlock( &count_mutex );
		
		if (count >= COUNT_DONE) return(NULL);

	}


}

void *functionCount2()
{

	for(;;)
	{

		if ( count < COUNT_HALT1 || count > COUNT_HALT2 )
		{
		
			// Signal to free waiting thread by freing the mutex.
			// Note: functionCount1() is now permitted to modify "count".

			pthread_cond_signal( &condition_var );

		}

		else
		{

			count++;	
			printf("Counter value functionCount2: %d \n", count);

		}
			
		pthread_mutex_unlock( &count_mutex );

		if(count >= COUNT_DONE) return(NULL);
	
	}

}
