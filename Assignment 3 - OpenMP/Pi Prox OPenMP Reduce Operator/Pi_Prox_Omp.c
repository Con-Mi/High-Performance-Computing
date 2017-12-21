/*
OpenMP calculating Pi constant.

Author: Marios Aspris.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stddef.h>

int main() {

  static size_t const n_steps = 100000000;
  double step, pi, sum = 0.0;
  size_t i;
  step = 1.0/(double)n_steps;

  double *x = malloc(n_steps * sizeof(double));
  for (i = 0; i < n_steps; ++i)
    x[i] = (i+0.5)*step;

  omp_set_num_threads(8);
  #pragma omp parallel for private(i) shared(x) schedule(dynamic, 100) reduction(+:sum) 
    for (i = 0; i < n_steps; ++i)
      sum += (4 / (1 + (x[i]*x[i])));

  free(x);

  pi = step*sum;
  printf("Pi equals = %.15f \n", pi);
  return 0;
}
