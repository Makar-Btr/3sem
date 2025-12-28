/*В Берляндии $n$ городов, связанных $m$ дорогами. Гарантируется, что изначально
граф из городов связный, т.е. существует путь между любой парой вершин.В
Берляндии происходит $q$ землетрясений, в ходе каждого из них разрушается
ровно одна дорога. Необходимо после каждого землетрясения узнать, является ли
полученный граф из городов связным. После очередного землетрясений дорога не
перестраивается, то есть разрушается навсегда.

Input
Первая строка входного файла содержит три числа $n$, $m$, $q$ (1≤n,m,q≤100000, 2≤n) (1≤n,m,q≤750000)
 - количество городов, дорог и землетрясений в Берляндии
соответственно.Следующие $m$ строк содержат по два натуральных числа $u$ и
$v$ $(1 \le u, v \le n)$ - номера городов, связанных дорогой. Гарантируется,
что $u \ne v$ и между каждой парой городов существует не больше одной
дороги.Следующие $q$ строк содержат по одному числу $x_i$ $(1 \le x_i \le m)$
- номер дороги, которая пострадает во время $i$-ого землетрясения.
Гарантируется, что два различных землетрясения не разрушают одну и ту же
дорогу.

Output
Выведите строку длины $q$ из нулей и единиц. $i$-ый символ равен 1, если после
$i$-ого землетрясения граф оказался связным, в противном случае выведите $0$.*/

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