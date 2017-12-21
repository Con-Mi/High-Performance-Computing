// Implementation of Djikstra algorithm with serialization.

#include <stdio.h>
#include <stdlib.h>

const int INFINITY = 1000000;

void Read_Matrix(int mat[], int n);
void Print_Matrix(int mat[], int n);
void Print_dists(int dist[], int n);
//void Print_paths(int pred[], int n);
int Find_min_dist(int dist[], int known[], int n);
void Dijkstra(int mat[], int dist[], int pred[], int n);


int main()
{
	int n;
	int *mat, *dist, *pred;

	printf("How many vertices! \n");
	scanf("%d", &n);
	mat = (int*) malloc(sizeof(int) * n*n);
	dist = (int*) malloc(sizeof(int) * n)
;	pred = (int*) malloc(sizeof(int) * n);

	printf("Enter the matrix \n");
	Read_matrix(mat, n);

	Dijkstra(mat, dist, pred, n);

	printf("The distance from 0 to each vertex is: \n");
	//Print_paths(pred, n);

	//free(mat);
	//free(dist);
	//free(ped);

	return 0;
}

// Self explanatory function.
void Read_matrix(int mat[], int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &mat[i*n+j]);
}

// Self explanatory function.
void Print_matrix(int mat[], int n)
{
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			if (mat[i*n+j] == INFINITY)
				printf("i ");
			else 
				printf("%d ", mat[i*n+j]);
		printf("\n");
	}
}

void Dijkstra(int mat[], int dist[], int pred[], int n) 
{
	int *known;
	known = (int *) malloc(sizeof(int) * n);
	
	dist[0] = 0; pred[0] = 0; known[0] = 1;
	for (int v = 1; v < n; ++v){
		dist[v] = mat[0*n + v];
		pred[v] = 0;
		known[v] = 0;
	}

	for (int i = 1; i < n; ++i){
		u = Find_min_dist(dist, known, n);

		known[u] = 1;

		for (int k = 1; k < n; ++k){
			if (!known[v])
			{
				new_dist = dist[u] + mat[u*n + v];
				if (new_dist < dist[v])
				{
					dist[v] = new_dist;
					pred[v] = u;
				}
			}
		}
	}

	free(known);

}


int Find_min_dist(int dist[], int known[], int n)
{
	best_so_far = INFINITY;
	for (int v = 1; v < n; ++v){
		if (dist[v] < best_so_far)
		{
			u = v;
			best_so_far = dist[v];
		}
	}
	return u;
}


void Print_dists(int dist[], int n)
{
	printf("  v   dist 0->v \n");
	printf("----  --------- \n");

	for (int i = 0; i < n; ++i)
		printf("%3d      %4d\n", i, dist[i]);
	printf("\n");
}

// add this function.
void Print_paths()
{

}