/* MPI Reduce algorithm */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_CONTRIB  20

int main(int argv, char **argc) {

  int size, my_rank;
  MPI_Comm comm;
  int x;
  int total;

  MPI_Init(NULL, NULL);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &my_rank);

  srandom(my_rank+1);
  x = random() % MAX_CONTRIB;
  printf("Poced %d > x = %d \n", my_rank, x);

  MPI_Allreduce(&x, &total, 1, MPI_INT, MPI_SUM, comm);

  if (my_rank == 0)
    printf("The total i %d \n", total);

  MPI_Finalize();
  return 0;
}
