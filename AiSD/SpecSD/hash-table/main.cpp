#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int m, c, n;
    fin >> m >> c >> n;

    vector<int> A(m, -1);

    int x, h;
    bool duplicate;
    for (int j = 1; j <= n; j++)
    {
        fin >> x;
        duplicate = false;
        for (int i = 0; i < m; i++)
        {
            if (A[i] == x)
            {
                duplicate = true;
                break;
            }
        }
        if (duplicate)
        {
            continue;
        }
        for (int i = 0; i < m; i++)
        {
            h = ((x % m) + i * c) % m;
            if (A[h] == -1)
            {
                A[h] = x;
                break;
            }
        }
    }

    for (int i : A)
    {
        fout << i << " ";
    }
    fout << endl;

    return 0;
}