#include "MarkerSystem.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <process.h>

using namespace std;

struct MarkerParams 
{
    int id;               
    int arraySize;        
    int* sharedArray;     
    CRITICAL_SECTION* cs; 
    HANDLE hStartEvent;   
    HANDLE hStoppedEvent; 
    HANDLE hStopEvent;    
    HANDLE hContinueEvent;
};

DWORD WINAPI MarkerThread(LPVOID lpParam) 
{
    MarkerParams* params = (MarkerParams*)lpParam;
    int id = params->id;
    int markedCount = 0;

    HANDLE waitEvents[2] = { params->hContinueEvent, params->hStopEvent };

    while (true) 
    {
        WaitForSingleObject(params->hStartEvent, INFINITE);
        bool collision = false;
        int collisionIndex = -1;
        srand(id);
        
        while (!collision) 
        {
            EnterCriticalSection(params->cs);
            
            int index = rand() % params->arraySize;
            if (params->sharedArray[index] == 0)
            {
                Sleep(5);
                params->sharedArray[index] = id;
                markedCount++;
                Sleep(5);
                LeaveCriticalSection(params->cs);
            } 
            else 
            {
                collision = true;
                collisionIndex = index;
                cout << "    Marker " << id << " stopped. Marks: " << markedCount 
                     << ". Collision at index " << collisionIndex << "." << endl;
                LeaveCriticalSection(params->cs);
            }
        }
        
        SetEvent(params->hStoppedEvent);
        
        WaitForSingleObject(params->hContinueEvent, INFINITE);

        if (WaitForSingleObject(params->hStopEvent, 0) == WAIT_OBJECT_0) 
        {
            EnterCriticalSection(params->cs);
            for (int i = 0; i < params->arraySize; ++i) 
            {
                if (params->sharedArray[i] == id) 
                {
                    params->sharedArray[i] = 0;
                }
            }
            LeaveCriticalSection(params->cs);
            delete params;
            return 0;
        } 
    }
    return 0;
}

MarkerSystem::MarkerSystem(int size, int count)
    : arraySize(size), markerCount(count), activeThreadsCount(count)
{
    if (arraySize <= 0 || markerCount <= 0) {
        throw std::invalid_argument("Array size and marker count must be positive.");
    }

    sharedArray = new int[arraySize]();
    InitializeCriticalSection(&cs);

    hThreadHandles.resize(markerCount);
    hStoppedEvents.resize(markerCount);
    hStopEvents.resize(markerCount);
    isThreadActiveVector.resize(markerCount, true);

    hContinueEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    for (int i = 0; i < markerCount; ++i) 
    {
        hStoppedEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL); 
        hStopEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);

        MarkerParams* params = new MarkerParams;
        params->id = i + 1;
        params->arraySize = arraySize;
        params->sharedArray = sharedArray;
        params->cs = &cs;
        params->hStartEvent = hStartEvent;
        params->hStoppedEvent = hStoppedEvents[i];
        params->hStopEvent = hStopEvents[i];
        params->hContinueEvent = hContinueEvent;

        hThreadHandles[i] = CreateThread(NULL, 0, MarkerThread, params, 0, NULL);
        if (hThreadHandles[i] == NULL) 
        {
            throw std::runtime_error("Failed to create thread.");
        }
    }
}

MarkerSystem::~MarkerSystem()
{
    for (int i = 0; i < markerCount; ++i) {
        if (isThreadActiveVector[i]) {
            terminateThread(i + 1);
        }
    }
    
    CloseHandle(hContinueEvent);
    CloseHandle(hStartEvent);
    DeleteCriticalSection(&cs);
    delete[] sharedArray;
}

void MarkerSystem::startAll()
{
    SetEvent(hStartEvent);
}

void MarkerSystem::waitForAllToStop()
{
    vector<HANDLE> hActiveStoppedEvents;
    for (int i = 0; i < markerCount; ++i) 
    {
        if (isThreadActiveVector[i]) 
        {
            hActiveStoppedEvents.push_back(hStoppedEvents[i]);
        }
    }

    if (hActiveStoppedEvents.empty()) 
    {
        return;
    }

    WaitForMultipleObjects((DWORD)hActiveStoppedEvents.size(), 
                            hActiveStoppedEvents.data(), TRUE, INFINITE);
}

void MarkerSystem::terminateThread(int id)
{
    int index = id - 1;
    if (index < 0 || index >= markerCount || !isThreadActiveVector[index]) {
        return;
    }

    isThreadActiveVector[index] = false;
    SetEvent(hStopEvents[index]);
    
    SetEvent(hContinueEvent); 

    WaitForSingleObject(hThreadHandles[index], INFINITE);

    CloseHandle(hThreadHandles[index]);
    CloseHandle(hStopEvents[index]);
    CloseHandle(hStoppedEvents[index]);

    activeThreadsCount--;

    ResetEvent(hContinueEvent);
}

void MarkerSystem::continueAll()
{
    if (activeThreadsCount == 0) return;
    
    ResetEvent(hStartEvent);
    SetEvent(hContinueEvent);
    ResetEvent(hContinueEvent); 
    SetEvent(hStartEvent);
}

std::vector<int> MarkerSystem::getArrayState()
{
    std::vector<int> copy(arraySize);
    EnterCriticalSection(&cs);
    memcpy(copy.data(), sharedArray, arraySize * sizeof(int));
    LeaveCriticalSection(&cs);
    return copy;
}

int MarkerSystem::getActiveThreadCount() const
{
    return activeThreadsCount;
}

bool MarkerSystem::isThreadActive(int id) const
{
    return isThreadActiveVector[id - 1];
}

void MarkerSystem::printArrayToConsole(const char* title)
{
    EnterCriticalSection(&cs);
    cout << title << endl;
    for (int i = 0; i < arraySize; ++i) 
    {
        cout << sharedArray[i] << " ";
    }
    cout << endl;
    LeaveCriticalSection(&cs);
}