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

    int u, v;
    for (int i = 1; i < n; i++)
    {
        fin >> u >> v;
        canon[v - 1] = u;
    }

    for (int i : canon)
    {
        fout << i << " ";
    }

    fout << endl;

    return 0;
}