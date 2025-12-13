#define UNICODE
#define _UNICODE

#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include "common.h"

void LogMessage(HANDLE hMutex, const std::wstring& message) {
    WaitForSingleObject(hMutex, INFINITE);
    std::wcout << message << std::endl;
    ReleaseMutex(hMutex);
}

void ProcessFile() {
    const int SIZE = 500;
    std::vector<char> data(SIZE);
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr) ^ GetCurrentProcessId()));
    std::uniform_int_distribution<int> dist('A', 'z');

    for (int i = 0; i < SIZE; ++i) data[i] = static_cast<char>(dist(rng));
    std::sort(data.begin(), data.end());
}

int main() {
    DWORD pid = GetCurrentProcessId();
    srand(static_cast<unsigned int>(time(NULL) ^ pid));

    HANDLE hSemaphore = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, SEMAPHORE_NAME);
    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, MUTEX_NAME);
    HANDLE hExitEvent = OpenEvent(SYNCHRONIZE, FALSE, EVENT_NAME);

    if (!hSemaphore || !hMutex || !hExitEvent) return 1;

    HANDLE waitHandles[2] = { hExitEvent, hSemaphore };
    DWORD waitResult = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

    if (waitResult == WAIT_OBJECT_0) {
        LogMessage(hMutex, L"[PID: " + std::to_wstring(pid) + L"] Cancelled (waiting in queue).");
    }
    else if (waitResult == WAIT_OBJECT_0 + 1) {
        LogMessage(hMutex, L"[PID: " + std::to_wstring(pid) + L"] -> Starting download...");

        if (WaitForSingleObject(hExitEvent, 0) == WAIT_OBJECT_0) {
            LogMessage(hMutex, L"[PID: " + std::to_wstring(pid) + L"] ! Aborted immediately.");
            ReleaseSemaphore(hSemaphore, 1, NULL);
        } else {
            ProcessFile(); 
            Sleep(1000 + (rand() % 4001));

            if (WaitForSingleObject(hExitEvent, 0) == WAIT_OBJECT_0) {
                LogMessage(hMutex, L"[PID: " + std::to_wstring(pid) + L"] ! Interrupted during process.");
            } else {
                LogMessage(hMutex, L"[PID: " + std::to_wstring(pid) + L"] + Done.");
                ReleaseSemaphore(hSemaphore, 1, NULL); 
            }
        }
    }

    CloseHandle(hSemaphore);
    CloseHandle(hMutex);
    CloseHandle(hExitEvent);
    return 0;
}