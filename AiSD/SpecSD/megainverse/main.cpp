#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a[i];
    }

    int lower, upper, total = 0;
    for (int j = 1; j < n - 1; j++)
    {
        lower = upper = 0;
        for (int i = 0; j - i >= 0 || j + i < n; i++)
        {
            if (j - i >= 0)
            {
                if (a[j - i] > a[j])
                {
                    lower++;
                }
            }
            if (j + i < n)
            {
                if (a[j + i] < a[j])
                {
                    upper++;
                }
            }
        }
        total += lower * upper;
    }

    fout << total << endl;


    return 0;
}