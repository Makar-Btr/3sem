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
    
    // Используем буферизацию
    fin.rdbuf()->pubsetbuf(nullptr, 8192);
    fout.rdbuf()->pubsetbuf(nullptr, 8192);

    int n, q;
    fin >> n >> q;

    DSU dsu(n);

    int x, y;
    for (int i = 0; i < q; i++)
    {
        fin >> x >> y;
        dsu.Union(x - 1, y - 1);

        fout << dsu.SetCount() << '\n';
    }

    return 0;
}