#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int rank, size;
    int number;
    MPI_Init(&argc, &argv);               // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
    if (rank == 0)
    {
        // Process 0 sends a message to process 1
        number = 10;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent number %d to Process 1\n", number);
    }
    else if (rank == 1)
    {
        // Process 1 receives a message from process 0
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d from Process 0\n", number);
    }
    MPI_Finalize(); // Finalize MPI
    return 0;
}