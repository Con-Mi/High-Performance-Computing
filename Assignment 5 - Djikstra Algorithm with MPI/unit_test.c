/*
Unit testing file.
Minimum Value works.
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_VAL 1000

void get_min_val(int *vec, int vec_size, int *min_val, int *idx);

int main() {

  int vec_size_is = 10;
  int *node_vec = calloc(10, sizeof(int));

  for (int i = 1; i < vec_size_is; ++i)
  {
    if (i%2==0)
      node_vec[i] = i;
  }
  int min_dist, idx_loc;

  get_min_val(node_vec, vec_size_is, &min_dist, &idx_loc);
  printf("The index of the minimum value is %d \n", idx_loc);
  printf("Minimum value is %d \n", min_dist);
  for (int i = 0; i < vec_size_is; ++i)
    printf("%d \n", node_vec[i]);

  free(node_vec);  
  return 0;


}

void get_min_val(int *vec, int vec_size, int *min_dist, int *idx) {
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
  *idx = tmpr_idx;
}
