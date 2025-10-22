#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N, K;
    const int mod = 1000000007;
    cin >> N >> K;

    if(K == 0 || K == N)
    {
        cout << "1";
        return 0;
    }

    vector<long long> fact(N + 1);
    fact[0] = 1;
    for(int i = 1; i <= N; i++)
    {
        fact[i] = (fact[i-1] * i) % mod;
    }


    long long divider = (fact[K] * fact[N - K]) % mod;
    //long long multiplier = pow(divider, mod - 2);
    //multiplier %= mod;
    /*long long multiplier = divider;
    for(int i = 2; i <= mod - 2; i++)
    {
        multiplier = (multiplier * divider) % mod;
    }*/
    long long multiplier = 1;
    long long exponent = mod - 2;
    while(exponent > 0)
    {
        if(exponent % 2 == 1)
        {
            multiplier = (multiplier * divider) % mod;
        }
        divider = (divider * divider) % mod;
        exponent /= 2;
    }
    
    long long result = (fact[N] * multiplier) % mod;
    cout << result;

    return 0;
}