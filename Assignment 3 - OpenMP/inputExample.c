// Example to read from a fle in C
// and save it as a vector of structs.

#include <stdio.h>
#include <stdlib.h>

struct StructVector {
	double x;
	double y;
	double z;
};

//struct StructVector Vec[11];

void main()
{
	double **Vec;
	int count = 0;
	double Vect;
	struct StructVector *StrVec;

	FILE *fp = fopen("cells.txt", "r");
	double c;
	// Read how many elements are contained in the file	
	// in order to know how to allocate the array.
	while (c = fscanf(fp, "%lf", &Vect))
	{
		if (c == EOF) break;
		count += 1;
	}
	fclose(fp);


	Vec = (double **) malloc(sizeof(double) * (count/3));
	for (int i = 0; i < (count/3); ++i)
		Vec[i] = (double *) malloc(sizeof(double) * 3);

	StrVec = (struct StructVector *) malloc(sizeof(struct StructVector) * 10);

	FILE *file = fopen("cells.txt", "r");
	
	for (int i = 0; i < 10; ++i)
		fscanf(file, "%lf %lf %lf", &StrVec[i].x, &StrVec[i].y, &StrVec[i].z);

	fclose(file);

	for (int i = 0; i < 10; ++i)
	{
		printf("%lf %lf %lf", StrVec[i].x, StrVec[i].y, StrVec[i].z);
		printf("\n");
	}


}