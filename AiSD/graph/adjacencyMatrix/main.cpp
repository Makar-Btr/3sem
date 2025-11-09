#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    int u, v;
    for (int i = 0; i < m; i++)
    {
        fin >> u >> v;
        graph[--u][--v] = 1;
        graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fout << graph[i][j] << " ";
        }
        fout << endl;
    }

    return 0;
}