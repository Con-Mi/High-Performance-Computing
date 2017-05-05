#include <stdio.h>
#include <time.h>

#define NewtonSum(x) ((x)*(x+1))/2

void main() {
	clock_t begin = clock();
	//unsigned long long  sum1 = 0;
	unsigned long long  sum2 = 0;
	unsigned long long  n = 1000000000;
	
	//for (unsigned long long i = 0; i < n+1; i++) {
	//	sum1 += i;		
	//}
	
	sum2 = NewtonSum(n);
	
	//printf("\n The sum of the first positive integers: %llu \n", sum1);
	printf("\n The sum with Newton's Method is: %llu  \n", sum2);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("\n Time spent for the program: %f secs \n", time_spent);
	
}
