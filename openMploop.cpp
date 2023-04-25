#include <stdio.h>
#include <omp.h>
#define N 100
int main()
{
    int i;
    int sum = 0;
    int a[N];
    // initialize the array with values from 1 to N
    for (i = 0; i < N; i++)
    {
        a[i] = i + 1;
    }
// parallel loop work sharing
#pragma omp parallel for reduction(+ \: sum)
    for (i = 0; i < N; i++)
    {
        sum += a[i];
    }
    printf("The sum of the array elements is %d.\n", sum);
    return 0;
}
// g++ -o openMploop openMploop.cpp 
// ./openMploop