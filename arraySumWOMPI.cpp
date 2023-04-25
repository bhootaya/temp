#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
const int N = 15;
const int P = 2;
int arr[N] = {25, 15, 32, 14, 23, 48, 63, 84, 23, 79, 18, 36, 48, 45, 29};
int psum[P] = {0};
void calc(int tid)
{
    int sind = tid * (N / P);
    int eind = (tid + 1) * (N / P);
    for (int i = sind; i < eind; i++)
    {
        psum[tid] += arr[i];
    }
}
int main()
{
    thread threads[P];
    for (int i = 0; i < P; i++)
    {
        threads[i] = thread(calc, i);
    }
    for (int i = 0; i < P; i++)
    {
        threads[i].join();
    }
    int sum = 0;
    for (int i = 0; i < P; i++)
    {
        sum += psum[i];
    }
    cout << "The sum of the array elements is " << sum << endl;
    return 0;
}