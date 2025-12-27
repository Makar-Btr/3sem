#include "SharedProtocol.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// Структура для хранения дескрипторов одного воркера
struct WorkerInfo
{
    HANDLE hPipeIn;         // Канал для отправки задач (Browser -> Worker)
    HANDLE hPipeOut;        // Канал для получения ответов (Worker -> Browser)
    PROCESS_INFORMATION pi; // Информация о процессе
};

int main()
{
    // Настройка локали для вывода кириллицы
    setlocale(LC_ALL, "Russian");

    int nWorkers = 0;
    int mTasks = 0;

    cout << "=== Browser Manager ===" << endl;
    cout << "Введите количество процессов-воркеров (N): ";
    cin >> nWorkers;
    cout << "Введите количество задач (M): ";
    cin >> mTasks;

    // Вектор для хранения информации о всех запущенных воркерах
    vector<WorkerInfo> workers(nWorkers);

    // 1. Создание каналов и запуск процессов
    for (int i = 0; i < nWorkers; ++i)
    {
        // Формируем имена каналов
        string pipeInName = "\\\\.\\pipe\\worker_in_" + to_string(i);
        string pipeOutName = "\\\\.\\pipe\\worker_out_" + to_string(i);

        // Создаем канал для ОТПРАВКИ (Outbound для сервера)
        workers[i].hPipeIn = CreateNamedPipeA(
            pipeInName.c_str(),
            PIPE_ACCESS_OUTBOUND, // Сервер пишет
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            1, // Макс. 1 экземпляр
            sizeof(TaskData), sizeof(TaskData), 0, NULL);

        // Создаем канал для ПОЛУЧЕНИЯ (Inbound для сервера)
        workers[i].hPipeOut = CreateNamedPipeA(
            pipeOutName.c_str(),
            PIPE_ACCESS_INBOUND, // Сервер читает
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1,
            sizeof(ResultData), sizeof(ResultData), 0, NULL);

        if (workers[i].hPipeIn == INVALID_HANDLE_VALUE ||
            workers[i].hPipeOut == INVALID_HANDLE_VALUE)
        {
            cerr << "Ошибка создания каналов для Worker " << i << endl;
            return 1;
        }

        // Запуск процесса Worker.exe с передачей ID через аргументы
        STARTUPINFOA si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&workers[i].pi, sizeof(workers[i].pi));

        string commandLine = "Worker.exe " + to_string(i);

        // ВАЖНО: CreateProcess требует non-const строку, поэтому создаем буфер
        vector<char> cmdBuffer(commandLine.begin(), commandLine.end());
        cmdBuffer.push_back(0);

        if (!CreateProcessA(NULL, cmdBuffer.data(), NULL, NULL, FALSE,
                            0, // Создаем отдельное окно для каждого воркера
                            NULL, NULL, &si, &workers[i].pi))
        {
            cerr << "Не удалось запустить Worker.exe. Убедитесь, что файл "
                    "существует."
                 << endl;
            return 1;
        }

        // Ожидаем подключения клиента к каналам (синхронизация)
        // В реальном приложении это лучше делать асинхронно, но здесь
        // упрощенная модель
        cout << "[Browser] Ожидание подключения Worker " << i << "..." << endl;
        ConnectNamedPipe(workers[i].hPipeIn, NULL);
        ConnectNamedPipe(workers[i].hPipeOut, NULL);
        cout << "[Browser] Worker " << i << " подключен." << endl;
    }

    cout << "\n--- Начало распределения задач ---\n" << endl;

    // 2. Распределение задач
    // Используем простой Round-Robin: отправляем задачу i-му воркеру по кругу
    // и сразу ждем ответа (синхронная модель, как описано в задании шаг 5)
    for (int t = 0; t < mTasks; ++t)
    {
        int workerIndex = t % nWorkers; // Выбираем воркера циклически
        WorkerInfo &currentWorker = workers[workerIndex];

        // Подготовка данных задачи
        TaskData task;
        task.command = CMD_PROCESS;
        task.length = ARRAY_SIZE;

        cout << "Задача #" << t << " -> Worker " << workerIndex << ": [ ";
        for (int k = 0; k < ARRAY_SIZE; ++k)
        {
            task.numbers[k] = rand() % 100; // Случайные числа 0-99
            cout << task.numbers[k] << " ";
        }
        cout << "]" << endl;

        // Отправка задачи
        DWORD bytesWritten;
        WriteFile(currentWorker.hPipeIn, &task, sizeof(TaskData), &bytesWritten,
                  NULL);

        // Ожидание и чтение результата (Блокировка Browser-а)
        ResultData result;
        DWORD bytesRead;
        ReadFile(currentWorker.hPipeOut, &result, sizeof(ResultData),
                 &bytesRead, NULL);

        cout << "Ответ  #" << t << " <- Worker " << result.workerId << ": [ ";
        for (int k = 0; k < ARRAY_SIZE; ++k)
        {
            cout << result.sortedNumbers[k] << " ";
        }
        cout << "]\n" << endl;
    }

    // 3. Завершение работы воркеров
    cout << "--- Все задачи выполнены. Завершение воркеров ---" << endl;

    for (int i = 0; i < nWorkers; ++i)
    {
        TaskData exitTask;
        exitTask.command = CMD_EXIT;
        DWORD bytesWritten;

        WriteFile(workers[i].hPipeIn, &exitTask, sizeof(TaskData),
                  &bytesWritten, NULL);

        // Ожидание завершения процесса
        WaitForSingleObject(workers[i].pi.hProcess, INFINITE);

        // Закрытие дескрипторов
        CloseHandle(workers[i].hPipeIn);
        CloseHandle(workers[i].hPipeOut);
        CloseHandle(workers[i].pi.hProcess);
        CloseHandle(workers[i].pi.hThread);

        cout << "[Browser] Worker " << i << " успешно завершен." << endl;
    }

    cout << "Browser завершает работу." << endl;
    system("pause");
    return 0;
}