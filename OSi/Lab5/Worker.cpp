#include "SharedProtocol.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// --- Алгоритм Сортировки Слиянием (Merge Sort) ---

// Функция слияния двух подмассивов
void Merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Временные массивы
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Рекурсивная функция сортировки
void MergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);

        Merge(arr, left, mid, right);
    }
}

// --- Основной код Worker ---

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc < 2)
    {
        cerr << "Ошибка: ID воркера не передан!" << endl;
        return 1;
    }

    // 1. Получение ID и формирование имен каналов
    int workerId = stoi(argv[1]);
    string pipeInName = "\\\\.\\pipe\\worker_in_" + to_string(workerId);
    string pipeOutName = "\\\\.\\pipe\\worker_out_" + to_string(workerId);

    cout << "Worker " << workerId << " запущен." << endl;

    // Ожидание готовности каналов (опционально, но полезно)
    WaitNamedPipeA(pipeInName.c_str(), NMPWAIT_WAIT_FOREVER);

    // 2. Подключение к каналам
    // Входной канал (открываем на чтение)
    HANDLE hPipeIn = CreateFileA(pipeInName.c_str(), GENERIC_READ, 0, NULL,
                                 OPEN_EXISTING, 0, NULL);

    // Выходной канал (открываем на запись)
    HANDLE hPipeOut = CreateFileA(pipeOutName.c_str(), GENERIC_WRITE, 0, NULL,
                                  OPEN_EXISTING, 0, NULL);

    if (hPipeIn == INVALID_HANDLE_VALUE || hPipeOut == INVALID_HANDLE_VALUE)
    {
        cerr << "Ошибка подключения к каналам в Worker " << workerId << endl;
        return 1;
    }

    cout << "Worker " << workerId << " подключен к Browser." << endl;

    bool running = true;
    TaskData task;
    DWORD bytesRead, bytesWritten;

    // 3. Основной рабочий цикл
    while (running)
    {
        // a. Чтение задачи (блокирующее)
        BOOL success =
            ReadFile(hPipeIn, &task, sizeof(TaskData), &bytesRead, NULL);

        if (!success || bytesRead == 0)
        {
            break; // Разрыв соединения
        }

        // b. Проверка типа команды
        if (task.command == CMD_EXIT)
        {
            cout << "Worker " << workerId << " получил команду завершения."
                 << endl;
            running = false;
        }
        else if (task.command == CMD_PROCESS)
        {
            cout << "Worker " << workerId << " получил задачу. Сортировка..."
                 << endl;

            // c. Выполнение вычислений (Сортировка слиянием)
            // Копируем данные в ResultData для сортировки in-place
            ResultData result;
            result.workerId = workerId;

            // Копируем входной массив в структуру результата
            for (int i = 0; i < task.length; i++)
            {
                result.sortedNumbers[i] = task.numbers[i];
            }

            // Запускаем сортировку
            MergeSort(result.sortedNumbers, 0, task.length - 1);

            // d. Отправка результата
            WriteFile(hPipeOut, &result, sizeof(ResultData), &bytesWritten,
                      NULL);

            cout << "Worker " << workerId << " отправил результат." << endl;
        }
    }

    // 4. Очистка ресурсов
    CloseHandle(hPipeIn);
    CloseHandle(hPipeOut);

    return 0;
}