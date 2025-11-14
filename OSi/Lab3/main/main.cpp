#include <iostream>
#include <vector>
#include <windows.h>
#include "MarkerSystem.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU.UTF-8");

    int arraySize;
    cout << "Введите размер массива: ";
    cin >> arraySize;

    int markerCount;
    cout << "Введите количество потоков marker: ";
    cin >> markerCount;

    try {
        MarkerSystem system(arraySize, markerCount);

        cout << markerCount << " потоков создано" << endl;
        
        system.startAll();

        while (system.getActiveThreadCount() > 0) 
        {
            system.waitForAllToStop();
            cout << "Main: Все активные потоки остановлены." << endl;

            system.printArrayToConsole("Main: Текущее состояние массива:");
        
            int idToTerminate = -1;
            bool validId = false;
            while (!validId) 
            {
                cout << "Введите номер потока для завершения (активные: ";
                for(int i = 0; i < markerCount; ++i) {
                    if(system.isThreadActive(i + 1)) {
                        cout << i + 1 << " ";
                    }
                }
                cout << "): ";
                cin >> idToTerminate;
                
                if (idToTerminate < 1 || idToTerminate > markerCount) {
                    cout << "Ошибка: неверный номер." << endl;
                } else if (!system.isThreadActive(idToTerminate)) {
                    cout << "Ошибка: поток " << idToTerminate << " уже завершен." << endl;
                } else {
                    validId = true;
                }
            }
            
            system.terminateThread(idToTerminate);

            system.printArrayToConsole("Main: Текущее состояние массива после очистки:");

            if (system.getActiveThreadCount() > 0) 
            {
                system.continueAll();
            }
        }

        cout << "\nВсе потоки marker завершены." << endl;

    } catch (const std::exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }
    
    cout << "Нажмите Enter для выхода." << endl;
    cin.ignore();
    cin.get();   

    return 0;
}