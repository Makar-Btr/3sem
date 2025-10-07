#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <algorithm>

void printWin32Error(const std::string& functionName) {
    DWORD errorCode = GetLastError();
    LPSTR errorMessage = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&errorMessage,
        0,
        nullptr
    );
    std::cerr << "Ошибка в функции " << functionName << ": " << errorMessage << std::endl;
    LocalFree(errorMessage);
}

void childProcess() {
    
    DWORD bytesRead;
    int arraySize = 0;
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), &arraySize, sizeof(int), &bytesRead, nullptr) || bytesRead == 0) {
        std::cerr << "Потомок: Не удалось прочитать размер массива." << std::endl;
        return;
    }
    
    std::vector<int> numbers(arraySize);
    if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), numbers.data(), arraySize * sizeof(int), &bytesRead, nullptr) || bytesRead == 0) {
        std::cerr << "Потомок: Не удалось прочитать элементы массива." << std::endl;
        return;
    }

    if (numbers.empty()) {
        std::cerr << "Потомок: Массив пуст, нет минимального элемента." << std::endl;
        return;
    }
    int minElement = *std::min_element(numbers.begin(), numbers.end());

    DWORD bytesWritten;
    if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &minElement, sizeof(int), &bytesWritten, nullptr)) {
        std::cerr << "Потомок: Не удалось записать результат." << std::endl;
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

    if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0)) {
        printWin32Error("CreatePipe (Pipe1)");
        return;
    }

    if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0)) {
        printWin32Error("CreatePipe (Pipe2)");
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
        printWin32Error("CreateProcessA");
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
        printWin32Error("WriteFile (arraySize)");
    }
    if (!WriteFile(hWritePipe1, numbers.data(), arraySize * sizeof(int), &bytesWritten, nullptr)) {
        printWin32Error("WriteFile (numbers)");
    }
    CloseHandle(hWritePipe1);

    int minElement;
    DWORD bytesRead;
    if (!ReadFile(hReadPipe2, &minElement, sizeof(int), &bytesRead, nullptr)) {
        printWin32Error("ReadFile (result)");
    }
    
    WaitForSingleObject(pi.hProcess, INFINITE);

    std::cout << "\nРодительский процесс получил результат от потомка: " << minElement << std::endl;

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