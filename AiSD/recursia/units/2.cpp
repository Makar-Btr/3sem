/*Дано число $N$. Необходимо определить, сколько есть бинарных строк длины $N$,
в которых ровно $K$ единиц.

Input
Первая строка входных данных содержит два целых неотрицательных числа $N$ и $K$
(0 \le K \le N \le 10^6).

Output
Выведите одно число - ответ на задачу. Так как ответ может быть очень большим,
необходимо его вывести по модулю*/

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    const int mod = 1000000007;
    cin >> N >> K;

    if (K == 0 || K == N)
    {
        cout << "1";
        return 0;
    }

    vector<long long> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        fact[i] = (fact[i - 1] * i) % mod;
    }

    long long divider = (fact[K] * fact[N - K]) % mod;
    long long multiplier = 1;
    long long exponent = mod - 2;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
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