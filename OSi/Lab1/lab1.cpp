#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
    int size;
    int* array;
    int numberOfEven;
} ThreadData;

/*DWORD WINAPI _workerThread(LPVOID data)
{
    ThreadData* threadData = (ThreadData*) data;
    threadData->numberOfEven = 0;
    
    for (int i = 0; i < threadData->size; i++)
    {
        if (threadData->array[i] % 2 == 0)
        {
            threadData->numberOfEven++;
        }
    }

    cout << "Number of even elements: " << threadData->numberOfEven << endl;
    return 0;
}*/

unsigned __stdcall workerThread(void* data)
{
    ThreadData* threadData = (ThreadData*) data;
    threadData->numberOfEven = 0;
    
    for (int i = 0; i < threadData->size; i++)
    {
        if (threadData->array[i] % 2 == 0)
        {
            threadData->numberOfEven++;
        }
    }

    cout << "Number of even elements: " << threadData->numberOfEven << endl;
    return 0;
}


int main()
{
    int sleepTime;
    ThreadData data;
    HANDLE worker;
    DWORD IDworker;

    cout << "enter the number of array elements: ";
    cin >> data.size;
    data.array = new int[data.size];
    for (int i = 0; i < data.size; i++)
    {
        data.array[i] = rand()%100;
        cout << data.array[i] << " ";
    }
    cout << endl;

    cout << "enter the stop and start time: ";
    cin >> sleepTime;

    //worker = CreateThread(NULL, 0, _workerThread, &data, 0, &IDworker);
    worker = (HANDLE)_beginthreadex(NULL, 0, workerThread, &data, 0, (unsigned*)&IDworker);
    SuspendThread(worker);
    Sleep(sleepTime);
    ResumeThread(worker);
    WaitForSingleObject(worker, INFINITE);

    CloseHandle(worker);

    return 0;
}