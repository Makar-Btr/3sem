/*Неориентированный граф задан списком рёбер. Постройте список смежности этого
графа. Гарантируется, что в графе нет петель и кратных рёбер.

Input
В первой строке записаны два целых числа n и m — число вершин (1 ≤ n ≤ 100 000)
и число рёбер графа (0 ≤ m ≤ 200 000). Вершины графа пронумерованы числами от 1
до n. В следующих m строках описаны рёбра: в каждой строке заданы через пробел
две вершины u и v (1 ≤ u, v ≤ n, причём u ≠ v), которые соединены ребром. 

Output
Выведите список смежности графа в виде n строк. В i-й строке выведите число
вершин, смежных с i-й вершиной, а затем номера этих вершин через пробел в
произвольном порядке.*/

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