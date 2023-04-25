#include <iostream>
#include <vector>
#include <numeric>
#include <future>
using namespace std;
int sum_chunk(vector<int> chunk)
{
    int s = 0;
    for (int i = 0; i < chunk.size(); i++)
        s += chunk[i];
    return s;
}
int parallel_sum(vector<int> arr, int p)
{
    /* Calculates the sum of all elements of an array using P processors. */
    int n = arr.size();
    int chunk_size = n / p;
    vector<vector<int>> chunks(p);
    for (int i = 0; i < p; i++)
    {
        chunks[i] = vector<int>(arr.begin() + i * chunk_size, arr.begin() + (i + 1) * chunk_size);
    }
    vector<future<int>> results(p);
    for (int i = 0; i < p; i++)
    {
        results[i] = async(launch::async, sum_chunk, chunks[i]);
    }
    int totalSum = 0;
    for (int i = 0; i < p; i++)
    {
        totalSum += results[i].get();
    }
    return totalSum;
}
int main()
{
    vector<int> arr = {12, 24, 36, 48, 13, 26, 39, 14, 28, 42, 15};
    int p = 2;
    int totalSum = parallel_sum(arr, p);
    cout << "The sum of the array elements is " << totalSum << endl;
    return 0;
}