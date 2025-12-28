/*Рассмотрим следующую модельную задачу. Изначально дана последовательность
чисел $A$ длины $n$ (индексация с нуля):

a_0, a_1, a_2, ..., a_{n-1}.

Поступают запросы двух типов.
Запрос модификации. Задан индекс $i$ и число $x$. Нужно прибавить к $i$-му
элементу число $x$.
Запрос суммы. Задана пара индексов $l$ и $r$. Нужно вычислить сумму элементов на
полуинтервале [l, r), т.е. a_l + a_{l+1} + ... + a_{r - 1}, и вернуть результат.

Input
В первой строке записано целое число $n$ — количество элементов массива ($1 \le
n \le 300\,000$).Во второй строке записаны $n$ целых чисел $a_i$ ($-10^9 \le a_i
\le 10^9$).В третьей строке записано целое число $q$ — количество запросов ($1
\le q \le 300\,000$).Каждая из следующих $q$ строк задаёт один запрос. Если это
запрос модификации, то в строке записано слово Add, затем индекс $i$ ($0 \le i <
n$) и число $x$ ($-10^9 \le x \le 10^9$). Если это запрос суммы, то он задаётся
словом FindSum и двумя индексами $l$ и $r$ ($0 \le l < r \le n$) — границами
полуинтервала.

Output
Для каждого запроса второго типа выведите в отдельной строке сумму элементов на
соответствующем полуинтервале.*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SegmentTree
{
  public:
    SegmentTree(vector<long long> &a)
    {
        n = a.size();
        tree.resize(4 * n, 0);
        Build(a, 0, 0, n);
    }

    void Add(int ind, long long val) { Adding(ind, val, 0, n, 0); }

    long long FindSum(int l, int r) { return Finding(l, r, 0, 0, n); }

  private:
    void Build(vector<long long> &a, int ind, int l, int r)
    {
        if (r - l == 1)
        {
            tree[ind] = a[l];
        }
        else
        {
            int mid = (l + r) / 2;
            Build(a, 2 * ind + 1, l, mid);
            Build(a, 2 * ind + 2, mid, r);
            tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
        }
    }

    void Adding(int ind, long long val, int l, int r, int v)
    {
        if (r - l == 1)
        {
            tree[v] += val;
            return;
        }

        int mid = (l + r) / 2;
        if (ind < mid)
        {
            Adding(ind, val, l, mid, 2 * v + 1);
        }
        else
        {
            Adding(ind, val, mid, r, 2 * v + 2);
        }
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    long long Finding(int l, int r, int v, int tl, int tr)
    {
        if (l == tl && r == tr)
        {
            return tree[v];
        }
        int mid = (tl + tr) / 2;
        if (r <= mid)
        {
            return Finding(l, r, 2 * v + 1, tl, mid);
        }
        if (mid <= l)
        {
            return Finding(l, r, 2 * v + 2, mid, tr);
        }
        return Finding(l, mid, 2 * v + 1, tl, mid) +
               Finding(mid, r, 2 * v + 2, mid, tr);
    }

  private:
    int n;
    vector<long long> tree;
};

int main()
{
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int q;
    cin >> q;

    SegmentTree tree(a);

    string instruction;
    int l, r, ind;
    long long val;
    for (int i = 0; i < q; i++)
    {
        cin >> instruction;
        if (instruction == "FindSum")
        {
            cin >> l >> r;
            cout << tree.FindSum(l, r) << endl;
        }
        if (instruction == "Add")
        {
            cin >> ind >> val;
            tree.Add(ind, val);
        }
    }

    return 0;
}