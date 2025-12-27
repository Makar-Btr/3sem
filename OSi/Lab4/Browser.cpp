#define UNICODE
#define _UNICODE

#include "common.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

int main()
{
    int N, M;

    std::cout << "--- Browser Manager ---\n";
    std::cout << "Enter max concurrent downloads (N): ";
    std::cin >> N;
    std::cout << "Enter total files in queue (M): ";
    std::cin >> M;

    if (N <= 0 || M <= N)
    {
        std::cout << "Error: N must be > 0 and M must be > N.\n";
        return 1;
    }

    HANDLE hSemaphore = CreateSemaphore(NULL, N, N, SEMAPHORE_NAME);

    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);

    HANDLE hExitEvent = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME);

    if (!hSemaphore || !hMutex || !hExitEvent)
    {
        std::cerr << "Failed to create synchronization objects." << std::endl;
        return 1;
    }

    std::cout << "\nBrowser is running. " << M << " tasks queued." << std::endl;
    std::cout << "Press Enter to close..." << std::endl;
    std::cout << "------------------------------------------------"
              << std::endl;

    std::vector<HANDLE> childProcesses;

    std::wstring cmdLine = L"Downloader.exe";

    for (int i = 0; i < M; ++i)
    {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::vector<wchar_t> cmdBuf(cmdLine.begin(), cmdLine.end());
        cmdBuf.push_back(0);

        if (!CreateProcess(NULL, cmdBuf.data(), NULL, NULL, FALSE, 0, NULL,
                           NULL, &si, &pi))
        {
            std::cerr << "Failed to create Downloader process #" << i
                      << std::endl;
        }
        else
        {
            childProcesses.push_back(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }

    std::cin.ignore();
    std::cin.get();

    std::cout << "------------------------------------------------"
              << std::endl;
    std::cout
        << "Browser is closing. Sending termination signal to all downloads..."
        << std::endl;

    SetEvent(hExitEvent);

    for (HANDLE hProc : childProcesses)
    {
        WaitForSingleObject(hProc, INFINITE);
        CloseHandle(hProc);
    }

    CloseHandle(hSemaphore);
    CloseHandle(hMutex);
    CloseHandle(hExitEvent);

    std::cout << "All downloads terminated. Browser closed." << std::endl;
    return 0;
}