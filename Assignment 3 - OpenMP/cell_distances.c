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

// Global variables
double *distances;
int nrOfBuckets = 3464; // Maximum number of buckets for the specfic problem.
double *buckets;
static size_t nrOfThreads;

// Struct for the coordinates.
struct coordinate {
	float x;
	float y;
	float z;
};

struct bucket {
	float value;
	int count;
};

struct coordinate *Cells;
// Function definitions
void get_distance(struct coordinate , struct coordinate consequent_cell);


////////////////////////////////////

// Main body.

int main(int argc, char *argv[]) {

	int opt;

	while ((opt = getopt(argc, argv, "t:")) != -1) 
	{
		switch(opt) {
		case "t":
			nr_threads = atoi(optarg);
			break;
		default:
			printf(stderr, "Usage %s [-t Number of Threads] \n", argv[0]);
			exit(EXIT_FAILURE);
	}

	// Read the file "cells.txt". First count how
	// many elements are in the file, in order to 
	// allocate the memory with the correct size, 
	// and avoid reallocation.

	double c;
	int counter = 0;
	double Vect;

	FILE *fp = fopen("cells.txt", "r");
	while (c = fscanf(fp, "%lf", Vect))
	{
		if (c == EOF) break;
		counter += 1;
	}
	fclose(fp)
	// I need to reopen the file.
	/*Cells = (double **) malloc(sizeof(double) * counter/3);
	for (int i = 0; i < counter/3; ++i)
		Cells[i] = (double *) malloc(sizeof(double) * 3);
	*/
	Cells = (struct coordinate *) malloc(sizeof(struct coordinate) * (counter/3)); 

	FILE file = fopen("cells.txt", "r");

	for (int i = 0; i < counter/3; ++i)
		for (int j = 0; j < 3; ++j)
			fscanf(file, "%lf %lf %lf", &Cells[i].x, &Cells[i].y, &Cells[i].z);

	fclose(file);
	
	#pragma omp parallel num_threads(nrOfThreads)
	get_sorted_distances();
}

////////////////////////////////////

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
