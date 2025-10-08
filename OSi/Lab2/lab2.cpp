#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>

void childProcess() {
    
    DWORD bytesRead;
    int arraySize = 0;
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), &arraySize, sizeof(int), &bytesRead, nullptr) || bytesRead == 0) {
        std::cerr << "Потомок: Ошибка в функции ReadFile (arraySize)." << std::endl;
        return;
    }
    
    std::vector<int> numbers(arraySize);
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), numbers.data(), arraySize * sizeof(int), &bytesRead, nullptr) || bytesRead == 0) {
        std::cerr << "Потомок: Ошибка в функции ReadFile (nummbers)." << std::endl;
        return;
    }

    if (numbers.empty()) {
        std::cerr << "Потомок: Массив пуст" << std::endl;
        return;
    }
    int maxElement = *std::max_element(numbers.begin(), numbers.end());

    DWORD bytesWritten;
    if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &maxElement, sizeof(int), &bytesWritten, nullptr)) {
        std::cerr << "Потомок: Ошибка в функции WriteFile (maxElement)." << std::endl;
        return;
    }

    CloseHandle(GetStdHandle(STD_INPUT_HANDLE));
    CloseHandle(GetStdHandle(STD_OUTPUT_HANDLE));
}

void parentProcess() {
    int arraySize;
    std::cout << "Введите размер массива: ";
    std::cin >> arraySize;

    std::vector<int> numbers(arraySize);
    std::cout << "Введите " << arraySize << " целых чисел: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cin >> numbers[i];
    }

    HANDLE hReadPipe1, hWritePipe1;
    HANDLE hReadPipe2, hWritePipe2;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0)) 
    {    
        std::cerr << "Родитель: Ошибка в функции CreatePipe (Pipe1)" << std::endl;
        return;
    }

    if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0)) {
        std::cerr << "Родитель: Ошибка в функции CreatePipe (Pipe2)" << std::endl;
        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        return;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    si.dwFlags |= STARTF_USESTDHANDLES;

    si.hStdInput = hReadPipe1;
    si.hStdOutput = hWritePipe2;
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    std::string commandLine = "D:\\3sem\\OSi\\Lab2\\lab2.exe child";
    
    if (!CreateProcessA(
        nullptr,
        const_cast<LPSTR>(commandLine.c_str()),
        nullptr,
        nullptr,
        TRUE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    )) {
        std::cerr << "Родитель: Ошибка в функции CreateProcessA" << std::endl;
        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        CloseHandle(hReadPipe2);
        CloseHandle(hWritePipe2);
        return;
    }

    CloseHandle(hReadPipe1);
    CloseHandle(hWritePipe2);

    DWORD bytesWritten;
    if (!WriteFile(hWritePipe1, &arraySize, sizeof(int), &bytesWritten, nullptr)) {
        std::cerr << "Родитель: Ошибка в функции WriteFile (arraySize)" << std::endl;
    }
    if (!WriteFile(hWritePipe1, numbers.data(), arraySize * sizeof(int), &bytesWritten, nullptr)) {
        std::cerr << "Родитель: Ошибка в функции WriteFile (numbers)" << std::endl;
    }
    CloseHandle(hWritePipe1);

    int minElement;
    DWORD bytesRead;
    if (!ReadFile(hReadPipe2, &minElement, sizeof(int), &bytesRead, nullptr)) {
        std::cerr << "Родитель: Ошибка в функции ReadFile (result)" << std::endl;
    }
    
    WaitForSingleObject(pi.hProcess, INFINITE);

    std::cout << "\nРодитель: Максимальный эллемент массива " << minElement << std::endl;

    CloseHandle(hReadPipe2);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "child") {
        childProcess();
    } else {
        parentProcess();
    }
    return 0;
}