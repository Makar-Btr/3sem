#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k, b = 0, l, r;
    vector<int> vec;

    cin >> n;
    
    int temp;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }
    cin >> k;
    int mid;
    int left, right;
    while (k)
    {
        cin >> temp;
        b = 0;
        left = 0, right = n;
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
        l = left;

        left = 0, right = n;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (vec[mid] <= temp)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        r = left;

        if (l < n && vec[l] == temp)
        {
            b = 1;
        }

        cout << b << " " << l << " " << r << endl;
        k--;
    }

    return 0;
}