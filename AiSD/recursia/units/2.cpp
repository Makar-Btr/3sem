#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int N, K;
    int mod = 1000000007;
    cin >> N >> K;
    vector<int> V(N + 1, 0);
    V[0] = 1;
    if(K == N || K == 0)
    {
        cout << "1";
        return 0;
    }

    if(K > N - K)
    {
        K = N - K;
    }

    for(int i = 1; i < N + 1; i++)
    {
        for(int j = min(i, K); j > 0; j--)
        {
            V[j] = (V[j - 1] % mod + V[j] % mod) % mod;
        }
    }

    cout << V[K];

    return 0;
}