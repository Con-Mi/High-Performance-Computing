#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void sumBoth(double* rowSums, double* colSums, const double** matrix, size_t nrs, size_t ncs) {
  for (size_t i = 0; i < nrs; i++) {
    rowSums[i] = 0;
  }
  for (size_t i = 0; i < ncs; i++) {
    colSums[i] = 0;
  }
  for (size_t i = 0; i < nrs; i++) {
    for (size_t j = 0; j < ncs; j++) {
      rowSums[i] += matrix[i][j];
      colSums[j] += matrix[i][j];
    }
  }
}

int main() {
	
	
	clock_t begin = clock();

	int nx = 1000;
	int ny = 1000;
	const size_t matrSize = 1000;	

	double** D2_array;
	D2_array = (double **)malloc(sizeof(double *)*nx);
	
	for(int i = 0; i < nx; i++)
		D2_array[i] = (double *)malloc(sizeof(double)*ny);		

	for (int y = 0; y < nx; y++) 
		for (int k = 0; k < nx; k++)
			D2_array[y][k] = 1;	
	
	double row_sum[matrSize];
	double col_sum[matrSize];

	sumBoth(row_sum, col_sum, (const double**) D2_array, matrSize, matrSize);

	clock_t end = clock();
	
	double time_spent = (double) (begin - end) / CLOCKS_PER_SEC;
	printf("\n The time spent is : %f \n", time_spent);
	return 0;
}
