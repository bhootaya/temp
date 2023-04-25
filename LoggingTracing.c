#include <stdio.h>
#include <mpi.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Enable MPI logging
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    MPI_File logfile;
    MPI_File_open(MPI_COMM_WORLD, "mpi_log.txt", MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &logfile);
    MPI_File_set_view(logfile, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
    // Log rank and size
    char logmsg[100];
    sprintf(logmsg, "Rank: %d, Size: %d\n", rank, size);
    MPI_File_write(logfile, logmsg, strlen(logmsg), MPI_CHAR, MPI_STATUS_IGNORE);
    // Log "Hello, World!" message
    sprintf(logmsg, "Hello, World! from Rank: %d\n", rank);
    MPI_File_write(logfile, logmsg, strlen(logmsg), MPI_CHAR, MPI_STATUS_IGNORE);
    // Synchronize all processes
    MPI_Barrier(MPI_COMM_WORLD);
    // Log "Goodbye, World!" message
    sprintf(logmsg, "Goodbye, World! from Rank: %d\n", rank);
    MPI_File_write(logfile, logmsg, strlen(logmsg), MPI_CHAR, MPI_STATUS_IGNORE);
    // Close the logfile
    MPI_File_close(&logfile);
    MPI_Finalize();
    return 0;
}