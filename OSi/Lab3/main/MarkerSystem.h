#pragma once

#include <vector>
#include <windows.h>
#include <stdexcept>

struct MarkerParams;

DWORD WINAPI MarkerThread(LPVOID lpParam);

class MarkerSystem
{
public:
    MarkerSystem(int size, int count);
    
    ~MarkerSystem();

    void startAll();

    void waitForAllToStop();

    void terminateThread(int id);

    void continueAll();

    std::vector<int> getArrayState();

    int getActiveThreadCount() const;
    bool isThreadActive(int id) const;

private:
    int arraySize;
    int markerCount;
    int* sharedArray;
    CRITICAL_SECTION cs;

    std::vector<HANDLE> hThreadHandles;
    std::vector<HANDLE> hStoppedEvents;
    std::vector<HANDLE> hStopEvents;
    HANDLE hContinueEvent;
    HANDLE hStartEvent;
    
    std::vector<bool> isThreadActiveVector;
    int activeThreadsCount;

    void printArrayToConsole(const char* title);
    
    friend int main(); 
};