#include <stdio.h>
#include <stdlib.h>

int*  allocated_array(int size_of_array) {

	int *arr;
	arr = (int *) malloc(sizeof(int)*size_of_array);
	return arr;
	
}

void main() {
	
	unsigned long long int bil = 1000000000;
	unsigned long long int sum;
	int size_of_array = 1000;
		
	int* a = allocated_array(size_of_array);

	for (unsigned long long int i = 0; i < bil+1; ++i)
		sum += i;
	
	printf("\n The sum of 1 billion integers is: %llu \n", sum);	

}
