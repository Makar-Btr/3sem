/*Необходимо из заданной числовой последовательности A, состоящей из n
элементов, вычеркнуть минимальное число элементов так, чтобы оставшиеся элементы
образовали строго возрастающую подпоследовательность элементов. Построенный
алгоритм должен иметь трудоёмкость O(n log n).

Note
Возрастание без разрывов подразумевает, что каждый следующий элемент
подпоследовательности строго больше предыдущего.

Input
Первая строка входного файла содержит число n (1 ≤ n ≤ 700 000). Следующая
строка содержит n элементов последовательности A, которые разделены пробелами
(элементы последовательности — целые числа, не превосходящие по модулю
1 000 000 000).

Output
Выведите одно число — длину строго возрастающей подпоследовательности
элементов.*/

#include <fstream>
#include <vector>

using namespace std;

int UpperBound(int temp, const vector<int> &vec, int size)
{
    int left = 0, right = size;
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (vec[mid] < temp)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;
    if (n == 0)
    {
        out << 0;
        return 0;
    }

    vector<int> V(n);
    for (int i = 0; i < n; i++)
    {
        in >> V[i];
    }

    vector<int> V2(n, INT_MAX);
    V2[0] = V[0];
    int length = 1, index;

    for (int i = 1; i < n; i++)
    {
        if (V[i] > V2[length - 1] && V[i] < V2[length])
        {
            V2[length++] = V[i];
        }
        else
        {
            V2[UpperBound(V[i], V2, length)] = V[i];
        }
    }

    out << length;

    return 0;
    ;
}