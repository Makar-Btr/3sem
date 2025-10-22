#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> first(n, 0);
    vector<int> second(n, 0);

    for(int i = 0; i < n; i++)
    {
        cin >> first[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin >> second[i];
    }

    vector<vector<int>> length(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(first[i - 1] == second[j - 1])
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
        if(first[i - 1] == second[j - 1])
        {
            firstIndex.push_back(i - 1);
            secondIndex.push_back(j - 1);
            i -= 1;
            j -= 1;
        }
        else if(length[i - 1][j] > length[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    cout << length[n][n] << endl;
    for(i = firstIndex.size() - 1; i >= 0; i--)
    {
        cout << firstIndex[i] << " ";
    }
    cout << endl;
    for(i = secondIndex.size() - 1; i >= 0; i--)
    {
        cout << secondIndex[i] << " ";
    }
    cout << endl;

    return 0;
}