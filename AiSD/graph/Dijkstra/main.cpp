/*Задан неориентированный взвешенный псевдограф, вершины которого пронумерованы
числами от 1 до n. Требуется найти кратчайшую цепь между вершинами 1 и n.
Гарантируется, что (1, n)-цепь существует.

Input
В первой строке содержатся целые числа n и m, где n — число вершин, а m — число
рёбер в псевдографе (1 ≤ n ≤ 200 000, 0 ≤ m ≤ 300 000). Далее в m строках
содержатся рёбра, по одному в строке. Каждое ребро задаётся тремя целыми числами
ui, vi, wi, где ui, vi — концы ребра, а wi — его длина (1 ≤ ui, vi ≤ n,
0 ≤ wi ≤ 11 111).

Output
Выведите длину кратчайшей цепи.*/

#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct point 
{
    int num;
    long long value;

    bool operator<(const point& other) const 
    {
        return value > other.value;
    }
};

class Web 
{
    int N, M;
    vector<vector<point>> A;
    vector<long long> bestWay;

public:
    Web() : N(0), M(0) {}

    void dijkstra() 
    {
        bestWay.resize(N, LLONG_MAX);
        bestWay[0] = 0;

        priority_queue<point> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            point p = pq.top();
            pq.pop();

            if (bestWay[p.num] < p.value) continue;

            for (int i = 0; i < A[p.num].size(); i++)
            {
                point next = A[p.num][i];
                if (bestWay[next.num] > bestWay[p.num] + next.value)
                {
                    bestWay[next.num] = bestWay[p.num] + next.value;
                    pq.push({next.num, bestWay[next.num]});
                }
            }

        }
    }

    long long answer()
    {
        return bestWay[N - 1];
    }

    friend ifstream& operator>>(ifstream& in, Web& obj);
};

ifstream& operator>>(ifstream& in, Web& obj) 
{
    in >> obj.N >> obj.M;

    obj.A.resize(obj.N);

    int s1, s2, pr;
    for (int i = 0; i < obj.M; i++) 
    {
        in >> s1 >> s2 >> pr;
        s1--;
        s2--;
        obj.A[s1].push_back({s2, pr});
        obj.A[s2].push_back({s1, pr});
    }

    return in;
}

int main() 
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    Web W;
    fin >> W;
    W.dijkstra();
    fout << W.answer() << endl;

    return 0;
}
