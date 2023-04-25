#include <stdio.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int rank, size, msg;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        // Synchronize all processes
        MPI_Barrier(MPI_COMM_WORLD);
        // Broadcast a message to all processes
        msg = 42;
        MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Gather data from all processes
        int data[size];
        MPI_Gather(&msg, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Print the gathered data
        printf("Rank 0 received:");
        for (int i = 0; i < size; i++)
        {
            printf(" %d", data[i]);
        }
        printf("\n");
    }
    else
    {
        // Synchronize all processes
        MPI_Barrier(MPI_COMM_WORLD);
        // Receive the broadcasted message from rank 0
        MPI_Bcast(&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Rank %d received message: %d\n", rank, msg);
        // Send data to rank 0 for gathering
        MPI_Gather(&msg, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}