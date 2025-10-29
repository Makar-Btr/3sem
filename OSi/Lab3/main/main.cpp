#include <iostream>
#include <vector>       
#include <windows.h>
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

void PrintArray(int* arr, int size, CRITICAL_SECTION* cs) 
{
    EnterCriticalSection(cs);
    for (int i = 0; i < size; ++i) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    LeaveCriticalSection(cs);
}

DWORD WINAPI MarkerThread(LPVOID lpParam) 
{
    MarkerParams* params = (MarkerParams*)lpParam;
    int id = params->id;
    int markedCount = 0;
    
    WaitForSingleObject(params->hStartEvent, INFINITE);

    srand(id);

    HANDLE waitEvents[2] = { params->hContinueEvent, params->hStopEvent };

    while (true) 
    {
        
        bool collision = false;
        int collisionIndex = -1;

        while (!collision) 
        {
            int index = rand() % params->arraySize;

            EnterCriticalSection(params->cs);

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
                
                LeaveCriticalSection(params->cs);
            }
        }
        cout << "    Marker " << id << " stopped. Marks: " << markedCount 
             << ". Collision at index " << collisionIndex << "." << endl;

        SetEvent(params->hStoppedEvent);

        DWORD waitResult = WaitForMultipleObjects(2, waitEvents, FALSE, INFINITE);

        if (waitResult == WAIT_OBJECT_0) 
        {
            cout << "--- Marker " << id << " resuming." << endl;
        } 
        else 
        {
            cout << "--- Marker " << id << " terminating." << endl;
        }
    }

    EnterCriticalSection(params->cs);

    cout << "--- Marker " << id << " cleaning up..." << endl;
    int cleanedCount = 0;
    for (int i = 0; i < params->arraySize; ++i) 
    {
        if (params->sharedArray[i] == id) 
        {
            params->sharedArray[i] = 0;
            cleanedCount++;
        }
    }
    cout << "--- Marker " << id << " cleaned " << cleanedCount << " marks." << endl;

    LeaveCriticalSection(params->cs);

    delete params;
    return 0;
}


int main() {
    setlocale(LC_ALL, "Russian");

    int arraySize;
    cout << "Введите размер массива: ";
    cin >> arraySize;
    if (arraySize <= 0) 
    {
        cout << "Неверный размер." << endl;
        return 1;
    }
    int* sharedArray = new int[arraySize]();

    int markerCount;
    cout << "Введите количество потоков marker: ";
    cin >> markerCount;
    if (markerCount <= 0 || markerCount > MAXDWORD) 
    {
        cout << "Неверное количество потоков." << endl;
        delete[] sharedArray;
        return 1;
    }

    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);

    vector<HANDLE> hThreadHandles(markerCount);
    vector<HANDLE> hStoppedEvents(markerCount);
    vector<HANDLE> hStopEvents(markerCount);
    vector<HANDLE> hContinueEvents(markerCount);
    vector<bool> isThreadActive(markerCount, true);
    int activeThreadsCount = markerCount;

    HANDLE hStartEvent = CreateEvent( NULL, TRUE, FALSE, NULL );

    for (int i = 0; i < markerCount; ++i) 
    {
        hStoppedEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
        hStopEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
        hContinueEvents[i] = CreateEvent( NULL, FALSE, FALSE, NULL );

        MarkerParams* params = new MarkerParams;
        params->id = i + 1;
        params->arraySize = arraySize;
        params->sharedArray = sharedArray;
        params->cs = &cs;
        params->hStartEvent = hStartEvent;
        params->hStoppedEvent = hStoppedEvents[i];
        params->hStopEvent = hStopEvents[i];
        params->hContinueEvent = hContinueEvents[i];

        hThreadHandles[i] = CreateThread(NULL, 0, MarkerThread, params, 0, NULL);
        if (hThreadHandles[i] == NULL) 
        {
            cerr << "Ошибка создания потока " << i + 1 << endl;
        }
    }

    cout << markerCount << " потоков создано" << endl;
    
    SetEvent(hStartEvent);

    while (activeThreadsCount > 0) 
    {
        
        vector<HANDLE> hActiveStoppedEvents;
        for (int i = 0; i < markerCount; ++i) 
        {
            if (isThreadActive[i]) 
            {
                hActiveStoppedEvents.push_back(hStoppedEvents[i]);
            }
        }

        if (hActiveStoppedEvents.empty()) 
        {
            break;
        }

        cout << "\nMain: Ожидание остановки " << activeThreadsCount << " потоков" << endl;
        WaitForMultipleObjects( (DWORD)hActiveStoppedEvents.size(), 
                                hActiveStoppedEvents.data(), TRUE, INFINITE );
        cout << "Main: Все активные потоки остановлены." << endl;

        cout << "Main: Текущее состояние массива:" << endl;
        PrintArray(sharedArray, arraySize, &cs);

        int idToTerminate = -1;
        bool validId = false;
        while (!validId) 
        {
            cout << "Введите номер потока для завершения (активные: ";
            for(int i=0; i<markerCount; ++i) 
            {
                if(isThreadActive[i]) 
                {
                    cout << i+1 << " ";
                }
            }
            cout << "): ";
            cin >> idToTerminate;
            
            if (idToTerminate < 1 || idToTerminate > markerCount) 
            {
                cout << "Ошибка: неверный номер." << endl;
            } 
            else if (!isThreadActive[idToTerminate - 1]) 
            {
                cout << "Ошибка: поток " << idToTerminate << " уже завершен." << endl;
            } 
            else 
            {
                validId = true;
            }
        }
        
        int indexToTerminate = idToTerminate - 1;

        isThreadActive[indexToTerminate] = false;
        SetEvent(hStopEvents[indexToTerminate]);

        WaitForSingleObject(hThreadHandles[indexToTerminate], INFINITE);
        cout << "Main: Поток " << idToTerminate << " завершен" << endl;

        CloseHandle(hThreadHandles[indexToTerminate]);
        CloseHandle(hStopEvents[indexToTerminate]);
        CloseHandle(hStoppedEvents[indexToTerminate]);
        CloseHandle(hContinueEvents[indexToTerminate]);

        activeThreadsCount--;

        cout << "Main: Текущее состояние массива:" << endl;
        PrintArray(sharedArray, arraySize, &cs);

        if (activeThreadsCount > 0) 
        {
            for (int i = 0; i < markerCount; ++i) 
            {
                if (isThreadActive[i]) 
                {
                    SetEvent(hContinueEvents[i]);
                }
            }
        }
    }

    cout << "\nВсе потоки marker завершены." << endl;

    CloseHandle(hStartEvent);
    DeleteCriticalSection(&cs);
    delete[] sharedArray;

    cout << "Нажмите Enter для выхода." << endl;
    cin.ignore();
    cin.get();   

    return 0;
}