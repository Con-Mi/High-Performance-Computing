/* Djikstra serialization in C */

#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>

#define MIN_VAL  1000

void find_min_dist(int *vec1);

int main(int argv, char **argc) {

  FILE *graph_file;
  int nodes1 = 0;
  int nodes2 = 0;
  int weights = 0;
  int file_size = 0;

  graph_file = fopen("example.txt", "r");
  while (fscanf(graph_file, "%d %d %d", &nodes1, &nodes2, &weights) != EOF)
  {
    ++file_size;
  }
  fclose(graph_file);


  int *w_vec = malloc(file_size * (sizeof(int)));
  int *i1_vec = malloc(file_size * (sizeof(int)));
  int *i2_vec = malloc(file_size * (sizeof(int)));
  int k = 0;

  graph_file = fopen("example.txt", "r");

  while (fscanf(graph_file, "%d %d %d", &i1_vec[k], &i2_vec[k], &w_vec[k]) != EOF)
  {
     ++k;
  }

  fclose(graph_file);

  int individual_nodes = 0;
  for (int i = 0; i < file_size-1; ++i)
  {
    if (i1_vec[i] != i1_vec[i+1])
      ++individual_nodes;
  }
  individual_nodes += 1;

  int **adj_matr = calloc(individual_nodes, sizeof(int*));
  for (int i = 0; i < individual_nodes; ++i)
    adj_matr[i] = calloc(individual_nodes, sizeof(int));

  /////////////////////////////////////////////////////
  // Make a method for this. Here it creates and adjacency matrix.
  int tmpr_nr = 0;
  for (int i = 0; i < individual_nodes; ++i)
  {
    while (i1_vec[tmpr_nr] == i)
    {
      adj_matr[i1_vec[tmpr_nr]][i2_vec[tmpr_nr]] = w_vec[tmpr_nr];
      ++tmpr_nr;
    }
  }
  // End.
  ///////////////////////////////////////////////////
  // Free the memory hold by the vectors.
  free(w_vec);
  free(i1_vec);
  free(i2_vec);
  // End.
  //////////////////////////////////////////////////

  for (int j = 0; j < individual_nodes; ++j)
  {
    for (int i = 0; i < individual_nodes; ++i)
      printf("%d  ", adj_matr[j][i]);
    printf("\n");
  }

  free(adj_matr);

  return 0;
}

void find_min_dist(int *vec, int vec_size, int *min_dist, int *idx_loc) {
  int i = 0;
  int tmpr_idx;
  int tmpr_min = MIN_VAL;
  do {
    if (vec[i] < tmpr_min && vec[i])
    {
      tmpr_min = vec[i];
      tmpr_idx = i;
    }
    ++i;
  } while( i < vec_size);
  *min_dist = tmpr_min;
  *idx_loc = tmpr_idx;
}
