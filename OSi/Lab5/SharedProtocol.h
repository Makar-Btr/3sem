#pragma once

const int ARRAY_SIZE = 10;

enum CommandType
{
    CMD_PROCESS = 1, // Выполнить задачу
    CMD_EXIT = 2     // Завершить работу
};

struct TaskData
{
    CommandType command;      // Тип команды
    int numbers[ARRAY_SIZE];  // Данные для обработки
    int length;               // Реальное количество элементов
};

struct ResultData
{
    int sortedNumbers[ARRAY_SIZE]; // Отсортированный массив
    int workerId;                  // ID 
};