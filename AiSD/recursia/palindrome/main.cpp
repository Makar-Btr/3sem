/*Вводится непустая строка S, которая имеет длину не более 7000 символов и
состоит только из строчных латинских букв. Необходимо удалить из строки
минимальное число символов так, чтобы получился палиндром (строка символов,
которая читается слева направо и справа налево одинаково).

Input
В первой строке записана исходная строка S.

Output
Выведите в первой строке длину получившегося палиндрома, а во второй строке сам
палиндром (если палиндромов несколько, то выведите только один из них).*/

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    string _string;
    in >> _string;

    int n = _string.size();
    if (n == 0)
    {
        out << "0" << endl;
        return 0;
    }

    vector<vector<int>> length(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        length[i][i] = 1;
    }

    for (int j = 1; j < n; j++)
    {
        for (int i = j - 1; i >= 0; i--)
        {
            if (_string[i] == _string[j])
            {
                length[i][j] = length[i + 1][j - 1] + 2;
            }
            else
            {
                length[i][j] = max(length[i + 1][j], length[i][j - 1]);
            }
        }
    }

    string palin;
    int i = 0, j = n - 1;
    while (i <= j)
    {
        if (_string[i] == _string[j])
        {
            palin += _string[i];
            i += 1;
            j -= 1;
        }
        else if (length[i + 1][j] > length[i][j - 1])
        {
            i++;
        }
        else
        {
            j--;
        }
    }

    string palindrome = palin;
    if (length[0][n - 1] % 2)
    {
        palin.erase(palin.size() - 1);
        reverse(palin.begin(), palin.end());
        palindrome += palin;
    }
    else
    {
        reverse(palin.begin(), palin.end());
        palindrome += palin;
    }

    out << length[0][n - 1] << endl << palindrome << endl;

    return 0;
}