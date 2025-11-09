#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct point 
{
    int num;
    int value;
    int from;

    point() : num(0), value(1e9), from(-1) {}
    point(int n, int s, int r) : num(n), value(s), from(r) {}
    bool operator<(const point& other) const 
    {
        return value > other.value;
    }
};

class Web 
{
    int N, M, start;
    vector<bool> visited;
    vector<vector<int>> A;
    vector<point> points;

public:
    Web() : N(0), M(0), start(0) 
    {
        
    }

    void show_matrix(ofstream& out) 
    {
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++) 
            {
                out << A[i][j] << '\t';
            }
            out << '\n';
        }
    }

    void dijkstra() 
    {
        priority_queue<point> Q;
        points[start].value = 0;
        points[start].num = start;
        points[start].from = start;
        Q.push(points[start]);
        while (!Q.empty()) 
        {
            point top = Q.top();
            Q.pop();
            if (visited[top.num]) continue;
            visited[top.num] = true;
            for (int i = 0; i < N; i++) 
            {
                if (top.value + A[top.num][i] < points[i].value) 
                {
                    points[i].value = top.value + A[top.num][i];
                    points[i].num = i;
                    points[i].from = top.num;
                    Q.push(points[i]);
                }
            }
        }
    }


    void show_points(ofstream& out) 
    {
        for (int i = 0; i < N; i++) 
        {
            out << (i + 1) << " " << points[i].value << " " << (points[i].from + 1) << '\n';
        }
    }

    int answer()
    {
        return points[N - 1].value;
    }

    ~Web() = default;


    friend ifstream& operator>>(ifstream& in, Web& obj);
};

ifstream& operator>>(ifstream& in, Web& obj) 
{
    in >> obj.N >> obj.M;
    obj.start = 0;
    obj.points.resize(obj.N);

    obj.visited.resize(obj.N, false);

    obj.A.resize(obj.N, vector<int>(obj.N, 1e9));
    for (int i = 0; i < obj.N; ++i)
    {
        obj.A[i][i] = 0;
    }

    int s1, s2, pr;
    for (int i = 0; i < obj.M; i++) 
    {
        in >> s1 >> s2 >> pr;
        s1--;
        s2--;
        if (obj.A[s1][s2] > pr)
        {
            obj.A[s1][s2] = pr;
            obj.A[s2][s1] = pr;
        }
    }

    return in;
}

int main() 
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    Web W;
    in >> W;
    W.dijkstra();
    out << W.answer() << endl;

    return 0;
}
