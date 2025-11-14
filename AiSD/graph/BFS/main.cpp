#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> BFS(vector<vector<int>>& graph, int size) 
{

    vector<int> result(size, 0);
    vector<bool> visited(size, false);

    int mark = 1;
    for (int start = 0; start < size; start++)
    {
        if (visited[start] == true)
        {
            continue;
        }
        
        queue<int> q;
        q.push(start);
        visited[start] = true;
        result[start] = mark++;


        while (!q.empty())
        {
            int top = q.front();
            q.pop();
            for (int i = 0; i < size; i++)
            {
                if (graph[top][i] == 1 && visited[i] == false)
                {
                    q.push(i);
                    visited[i] = true;
                    result[i] = mark++;
                }
            }
        }
    }

    return result;
}

int main() 
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> graph[i][j];
        }
    }

    for (int i : BFS(graph, n))
    {
        fout << i << " ";
    }
    fout << endl;

    return 0;
}