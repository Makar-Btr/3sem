/*Даны две последовательности $A$ и $B$, каждая имеет длину $n$.Найти наибольшее
$k$, для которого существуют две последовательности индексов $0 \le i_1 < i_2
< \ldots < i_k < n$ и $0 \le j_1 < j_2 < \ldots < j_k < n$, что $A_{i_1} =
B_{j_1}$, $A_{i_2} = B_{j_2}$, …, $A_{i_k} = B_{j_k}$.Также нужно найти и
сами последовательности индексов.

Input
В первой строке записано число $n$ ($1 \le n \le 1000$), длина
последовательностей $A$ и $B$.Во второй строке содержится $n$ целых чисел $a_i$
($1 \le a_i \le 1000$) — элементы последовательности $A$.В третьей строке
содержатся $n$ целых чисел $b_j$ ($1
\le b_j \le 1000$) — элементы последовательности $B$.

Output
В первой строке выведите число $k$. Во второй строке выведите индексы $i_{1}\,
i_{2}\,
\ldots\, i_k$.В третьей строке выведите индексы $j_{1}\, j_{2}\, \ldots\,
j_k$.Если подходящий последовательностей индексов несколько, выведите любые
из них.*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> first(n, 0);
    vector<int> second(n, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> first[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> second[i];
    }

    vector<vector<int>> length(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (first[i - 1] == second[j - 1])
            {
                length[i][j] = length[i - 1][j - 1] + 1;
            }
            else
            {
                length[i][j] = max(length[i - 1][j], length[i][j - 1]);
            }
        }
    }

    vector<int> firstIndex;
    vector<int> secondIndex;

    int i = n, j = n;
    while (length[i][j] != 0)
    {
        if (first[i - 1] == second[j - 1])
        {
            firstIndex.push_back(i - 1);
            secondIndex.push_back(j - 1);
            i -= 1;
            j -= 1;
        }
        else if (length[i - 1][j] > length[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    cout << length[n][n] << endl;
    for (i = firstIndex.size() - 1; i >= 0; i--)
    {
        cout << firstIndex[i] << " ";
    }
    cout << endl;
    for (i = secondIndex.size() - 1; i >= 0; i--)
    {
        cout << secondIndex[i] << " ";
    }
    cout << endl;

    return 0;
}