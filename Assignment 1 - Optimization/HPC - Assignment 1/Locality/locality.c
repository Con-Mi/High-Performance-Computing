#include <stddef.h>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>

void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs) {

	for ( size_t ix = 0; ix < nrs; ++ix ) {
		double sum = 0;

		for ( size_t jx = 0; jx < ncs; ++jx ) {
			sum += matrix[ix][jx];
		} 

		sums[ix] = sum;
	}	

}
 
void col_sums( double * sums,  const double ** matrix, size_t nrs, size_t ncs ) {

	for ( size_t jx = 0; jx < ncs; ++jx) {
		double sum = 0;

		for ( size_t ix = 0; ix < nrs; ++ix ) {
			sum += matrix[ix][jx];
		}
		
		sums[jx] = sum;		
	}
}

/*double** Make2DDoubleArray(int arraySizeX, int arraySizeY) {

	double** array;
	array = (double**) malloc(arraySizeX*sizeof(double*));
	for (int i = 0; i < arraySizeX; i++) 
		array[i] = (double*) malloc(arraySizeY*sizeof(double));
		return array;			

}*/

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

	row_sums(row_sum, (const double**) D2_array, nx, ny);
	col_sums(col_sum, (const double**) D2_array, nx, ny);

	clock_t end = clock();
	
	double time_spent = (double) (begin - end) / CLOCKS_PER_SEC;
	printf("\n The time spent is : %f \n", time_spent);
	
	return 0;

}
