#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int n;
    cin >> n;
    vector<int> kuvshinki(n, 0);
    for(int i = 0; i < n; i++)
    {
        cin >> kuvshinki[i];
    }

    vector<int> komarihi(n, -1);
    vector<int> from(n, -1);
    komarihi[0] = kuvshinki[0];
    if(kuvshinki.size() >= 3)
    {
        komarihi[2] = kuvshinki[2] + komarihi[0];
        from[2] = 0;
    }
    for(int i = 3; i < n; i++)
    {
        if(komarihi[i - 2] != -1)
        {
            komarihi[i] = komarihi[i - 2] + kuvshinki[i];
            from[i] = i - 2;
        }
        if(komarihi[i - 3] != -1 && komarihi[i - 3] + kuvshinki[i] > komarihi[i])
        {
            komarihi[i] = komarihi[i - 3] + kuvshinki[i];
            from[i] = i - 3;
        }
    }

    if(komarihi[n - 1] == -1)
    {
        cout << -1;
        return 0;
    }

    vector<int> way;
    int temp = n - 1;
    while(temp > -1)
    {
        way.push_back(temp + 1);
        temp = from[temp];
    }
    reverse(way.begin(), way.end());

    cout << komarihi[n-1] << endl;
    for(int i = 0; i < way.size(); i++)
    {
        cout << way[i] << " ";
    }

    return 0;
}