#include <fstream>
#include <vector>

using namespace std;

class DSU
{
public:
    DSU(int n) : m_count(n)
    {
        m_parent.resize(n);
        m_size.resize(n);
        for (int i = 0; i < n; i++)
        {
            m_parent[i] = i;
            m_size[i] = 1;
        }
    }
    int FindSet(int x)
    {
        if (m_parent[x] == x)
        {
            return x;
        }
        return m_parent[x] = FindSet(m_parent[x]);
    }
    void Union(int x, int y)
    {
        int xRoot = FindSet(x);
        int yRoot = FindSet(y);
        if (xRoot == yRoot)
        {
            return;
        }

        m_count--;
        
        if (m_size[xRoot] < m_size[yRoot])
        {
            m_parent[xRoot] = yRoot;
            m_size[yRoot] += m_size[xRoot];
        }
        else
        {
            m_parent[yRoot] = xRoot;
            m_size[xRoot] += m_size[yRoot];
        }
        
    }
    int SetCount()
    {
        return m_count;
    }

private:
    vector<int> m_parent;
    vector<int> m_size;
    int m_count;
};


int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m, q;
    fin >> n >> m >> q;

    vector<pair<int, int>> roads(m + 1);

    for (int i = 1; i <= m; i++)
    {
        fin >> roads[i].first >> roads[i].second;
        roads[i].first--;
        roads[i].second--;
    }

    vector<int> earthquakes(q);
    vector<bool> destroyed(m + 1, false);

    for (int i = 0; i < q; i++)
    {
        fin >> earthquakes[i];
        destroyed[earthquakes[i]] = true;
    }
    
    DSU dsu(n);
    for(int i = 1; i <= m; i++)
    {
        if (!destroyed[i])
        {
            dsu.Union(roads[i].first, roads[i].second);
        }
    }

    vector<bool> result(q);

    for (int i = q - 1; i >= 0; i--) 
    {
        result[i] = (dsu.SetCount() == 1);
        
        int road = earthquakes[i];
        dsu.Union(roads[road].first, roads[road].second);
    }

    for (int i = 0; i < q; i++) 
    {
        fout << (result[i] ? '1' : '0');
    }
    fout << endl;


    return 0;
}