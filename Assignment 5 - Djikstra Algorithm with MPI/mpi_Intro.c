// Intro to MPI.

#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void)
{
	char greeting[MAX_STRING];
	int my_rank, p , q;

	// Start MPI.
	MPI_Init(NULL, NULL);

	// Get the number of processes.
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// Get the rank.
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) 
	{
		printf("Greetings from processes %d of %d \n", my_rank, p);
		for (int q = 1; q < p; ++q)
		{
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s \n", greeting);
		}
	}
	else
	{
		sprintf(greeting, "Greetings from process %d of %d", my_rank, p);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	// Shut down MPI
	MPI_Finalize();
	return 0;
}