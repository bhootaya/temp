#include <iostream>
#include <pthread.h>
using namespace std;

void *print(void *Tid)
{
    long tid = (long)Tid;
    cout << "This is thread no." << tid << endl;
    pthread_exit(NULL);
}
int main()
{
    const int n = 5;
    pthread_t threads[n];
    int flag;
    for (long i = 0; i < n; i++)
    {
        cout << "Creating thread no." << i << endl;
        flag = pthread_create(&threads[i], NULL, print, (void *)i);
        if (flag)
        {
            cout << "Error: unable to create thread, " << flag << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
// g++ -pthread -o helloWorld HelloWORLD.cpp -> make object file
// run object file -> ./helloWorld