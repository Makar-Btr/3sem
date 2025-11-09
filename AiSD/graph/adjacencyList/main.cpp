#include <fstream>
#include <vector>
#include <list>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    vector<list<int>> graph(n);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        fin >> u >> v;
        graph[--u].push_front(--v);
        graph[v].push_front(u);
    }

    for (int i = 0; i < n; i++)
    {
        fout << graph[i].size() << " ";
        for (int j : graph[i])
        {
            fout << j + 1 << " ";
        }
        fout << endl;
    }

    return 0;
}