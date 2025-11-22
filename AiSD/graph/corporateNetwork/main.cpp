#include <fstream>
#include <vector>

using namespace std;

class DSU
{
public:
    DSU(int n)
    {
        m_parent.resize(n + 1);
        m_dist.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            m_parent[i] = i;
            m_dist[i] = 0;
        }
    }

    int FindSet(int x)
    {
        if (m_parent[x] == x)
        {
            return x;
        }

        int root = x;
        vector<int> m_path;
        while (m_parent[root] != root)
        {
            m_path.push_back(root);
            root = m_parent[root];
        }
        
        for (int i = m_path.size() - 1; i >= 0; i--)
        {
            int node = m_path[i];
            int old_parent = m_parent[node];

            m_dist[node] += m_dist[old_parent];
            
            m_parent[node] = root;
        }
        
        return root;
    }

    void Union(int i, int j)
    {
        m_parent[i] = j;
        
        m_dist[i] = abs(i - j) % 1000;
    }

    long long GetDist(int x)
    {
        FindSet(x);
        return m_dist[x];
    }

private:
    vector<int> m_parent;
    vector<long long> m_dist;
};

class Graph
{
public:
    Graph(int n) : m_graph(n) {}

    void I(int i, int j)
    {
        m_graph.Union(i, j);
    }

    long long E(int i)
    {
        return m_graph.GetDist(i);
    }

private:
    DSU m_graph;
};

int main() 
{
    ios_base::sync_with_stdio(false);
    
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    if (!(fin >> n)) return 0;

    Graph graph(n);

    char command;
    int i, j;
    while (fin >> command)
    {
        if (command == 'O') break;

        switch (command)
        {
            case 'E':
            {
                fin >> i;
                fout << graph.E(i) << endl;
                break;
            }
            case 'I':
            {
                fin >> i >> j;
                graph.I(i, j);
                break;
            }
            default:
                break;
        }
    }
    return 0;
}