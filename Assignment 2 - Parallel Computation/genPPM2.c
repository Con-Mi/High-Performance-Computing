#include <stdio.h>

int main()
{

	const char *filename = "n.ppm";
	
	// size of image
	const int x_max = 100;
	const int y_max = 100;
	// 2D array for colors
	unsigned char data[y_max][x_max];
	// color component is coded from 0 to 255
	const int MaxColorComponentValue = 255;
	FILE * fp;
	
	// array
	for (int i = 0; i < y_max; ++i)
		for (int j = 0; j < x_max; ++j)
			data[i][j] = (i + j) & 255;
		
	// write in a ppm file
	fp = fopen(filename, "wb");

	fprintf(fp, "P5\n %d\n %d\n %d\n", x_max, y_max, MaxColorComponentValue);
	
	// write
	fwrite(data, sizeof(data), 1, fp);
	fclose(fp);


	return 0;
}
	
	
