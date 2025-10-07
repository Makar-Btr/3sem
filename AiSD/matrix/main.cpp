#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int s, n, m;

    in >> s;

    vector<int> sizes(s + 1, 0);
    for(int i = 0; i < s; i++)
    {
        in >> n >> m;
        if(i == 0)
        {
            sizes[i] = n;
        }
        sizes[i + 1] = m;
    }

    vector<vector<long long>> costs(s + 1, vector<long long>(s + 1, 0));

    int j;
    long long cost = 0;
    for(int l = 2; l <= s; l++)
    {
        for(int i = 1; i <= s - l + 1; i++)
        {
            j = i + l - 1;
            costs[i][j] = LLONG_MAX;
            for(int k = i; k < j; k++)
            {
                cost = costs[i][k] + costs[k + 1][j] + (long long)(sizes[i - 1] * sizes[k] * sizes[j]);
                if(cost < costs[i][j])
                {
                    costs[i][j] = cost;
                }
            }
        }
    }

    out << costs[1][s];
    return 0;
}