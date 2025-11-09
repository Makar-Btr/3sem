#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<int> canon(n);

    int u;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> u;
            if (u == 1)
            {
                canon[j] = i + 1;
            }
        }
    }

    for (int i : canon)
    {
        fout << i << " ";
    }

    fout << endl;

    return 0;
}