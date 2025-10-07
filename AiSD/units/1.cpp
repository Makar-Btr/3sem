#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, K;
    int mod = 1000000007;
    cin >> N >> K;
    vector<vector<int>> V(N + 1, vector<int>(N + 1, 0));

    for(int i = 0; i < N + 1; i++)
    {
        V[i][i] = 1;
        V[i][0] = 1;
    }
    for(int i = 1; i < N + 1; i++)
    {
        for(int j = 1; j <= i - 1; j++)
        {
            V[i][j] = (V[i - 1][j - 1] % mod + V[i - 1][j] % mod) % mod;
        }
    }

    cout << V[N][K];

    return 0;
}