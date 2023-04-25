#include <stdio.h>
#include <omp.h>
int main()
{
    int tid;
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
#pragma omp sections nowait
        {
#pragma omp section
            {
                printf("Thread %d is executing section 1\n", tid);
            }
#pragma omp section
            {
                printf("Thread %d is executing section 2\n", tid);
            }
#pragma omp section
            {
                printf("Thread %d is executing section 3\n", tid);
            }
        }
    }
    return 0;
}
// mpicc -fopenmp openMpSection.c -o openMpsection
// mpirun -np 3 ./openMpsection