/*Для ориентированного графа, заданного матрицей смежности, выполнили поиск в
ширину. При неоднозначности выбора очередной вершины всегда выбирали вершину с
меньшим номером. В процессе поиска в ширину в момент посещения вершины ей
присваивали метку (нумерация меток начинается с единицы). Определите, какую
метку получила каждая из вершин графа (поиск в ширину выполняли до тех пор, пока
все вершины не получили метки).

Input
В первой строке записано целое число n вершин орграфа (1 ≤ n ≤ 100). Вершины
нумеруются числами от 1 до n. Далее записана матрица смежности графа: n строк по
n чисел, каждое из которых — 0 или 1. Числа разделяются одиночными пробелами.
Гарантируется, что все элементы на главной диагонали нулевые. 

Output 
Выведите n чисел, i-е из которых — метка, которую получила вершина i.*/

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