/*На вход подаются две символьные последовательности A и B, каждая
последовательность непустая, состоит из маленьких латинских букв и имеет длину
не более 1000 символов. Необходимо преобразовать последовательность A в
последовательность B с минимальным суммарным штрафом, который определяется
следующим образом:

удаление символа из строки A равно x баллов;
вставка символа в строку A равна y баллов;
замена символа в строке A на любой другой равна z баллов.

Input
В первых трёх строках находятся числа x, y, z соответственно. Все числа целые
положительные и не превосходят 1 000 000. В следующих двух строках находятся
символьные последовательности A и B (тип элементов последовательности string).

Output
Выведите минимальный суммарный штраф.*/

#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");

    int delet, insert, replace;
    in >> delet >> insert >> replace;
    string A, B; //A->B
    in >> A >> B;

    vector<vector<int>> distance(A.size() + 1, vector<int>(B.size() + 1, 0));
    for(int i = 1; i <= A.size(); i++)
    {
        distance[i][0] = i * delet;
    }
    for(int i = 1; i <= B.size(); i++)
    {
        distance[0][i] = i * insert;
    }

    for(int i = 1; i <= A.size(); i++)
    {
        for(int j = 1; j <= B.size(); j++)
        {
            if(A[i - 1] != B[j - 1])
            {
                distance[i][j] = min(min(distance[i - 1][j] + delet, 
                                         distance[i][j - 1] + insert), 
                                     distance[i - 1][j - 1] + replace);
            }
            else
            {
                distance[i][j] = min(min(distance[i - 1][j] + delet, 
                                         distance[i][j - 1] + insert), 
                                     distance[i - 1][j - 1]);
            }
        }
    }

    out << distance[A.size()][B.size()] << endl;

    return 0;
}