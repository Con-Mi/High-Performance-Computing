/*
 Distances between three dimensional points.
 Values for x, y, z, is between [-10, 10].
 Sorting the distances between the points using 
 bucket sort. Number of buckets is set to 3465
 due to the problem specification, of maximum distance
 that can occur.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>


// Function definitions
//void get_distance(struct coordinate , struct coordinate consequent_cell);




/* Main body. */

int main(int argc, char **argv) {

	/* User inputs to the program. */
	int opt;
	int nr_threads;
	while ((opt = getopt(argc, argv, "t:")) != -1) 
	{
		switch(opt) {
		case 't':
			nr_threads = atoi(optarg);
			break;
		default:
			fprintf(stderr, "Usage %s [-t Number of Threads] (without brackets.)\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	/* 		   End of user input.		*/
	
	
	float *x, *y, *z;
	int file_size = 0;
	float tmpr1, tmpr2, tmpr3;

	FILE *fp = fopen("cells.txt", "r");
	while (fscanf(fp, "%f %f %f", &tmpr1, &tmpr2, &tmpr3) != EOF)
	{
		++file_size;
	}
	fclose(fp);
	
	int i = 0;
	x = malloc(file_size * sizeof(float));
	y = malloc(file_size * sizeof(float));
	z = malloc(file_size * sizeof(float));

	fp = fopen("cells.txt", "r");
	while (fscanf(fp, "%f %f %f", &x[i], &y[i], &z[i]) != EOF)
	{
		++i;
	}
	fclose(fp);
	printf("z[4] = %f \n", z[4]);
	
	// In the calulate distances function I should use the reduce operator.
	// Its like matrix multiplication, but keeping track of the index.
	//calculate_distances()
	
	/*
	// I need to reopen the file.
	//Cells = (double **) malloc(sizeof(double) * counter/3);
	for (int i = 0; i < counter/3; ++i)
		Cells[i] = (double *) malloc(sizeof(double) * 3);
	//
	Cells = malloc(sizeof(struct coordinate) * (counter/3)); 

	FILE file = fopen("cells.txt", "r");

	for (int i = 0; i < counter/3; ++i)
		for (int j = 0; j < 3; ++j)
			fscanf(file, "%lf %lf %lf", &Cells[i].x, &Cells[i].y, &Cells[i].z);

	fclose(file);
	
	#pragma omp parallel num_threads(nrOfThreads)
	get_sorted_distances();
	*/
	free(x);
	free(y);
	free(z);
	return 0;
	
}

////////////////////////////////////
/*
void get_sorted_distances(struct coordinate Cells[], struct bucket buckets[])
{
	for (int i = 0; i < counter/3; ++i) {
		double distans = sqrt( ( (Cells[i].x - Cells[i+1].x) * (Cells[i].x - Cells[i+1].x) ) \
							 + ( (Cells[i].y - Cells[i+1].y) * (Cells[i].y - Cells[i+1].y) ) \
							  + ( (Cells[i].z - Cells[i+1].z) * (Cells[i].z - Cells[i+1].z) ) );	
		distans = round(distans * 100.0)/100.0;

		if (distans < 0.00000000001)
			buckets[nrOfBuckets / 2] = distans;
		else
			buckets[distans * 100] = distans;
	}
}
*/
