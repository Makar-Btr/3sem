/*Мегаинверсией в перестановке p1, p2, …, pn назовём тройку (i, j, k), для
которой i < j < k и pi > pj > pk.

Input
Первая строка содержит целое число n (1 ≤ n ≤ 300 000).
Следующие n строк описывают перестановку: i-я строка содержит одно целое число
pi (1 ≤ pi ≤ n; все pi попарно различны).

Output
Выведите число мегаинверсий в перестановке p1, p2, …, pn.*/

#include <fstream>
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

    SegmentTree(int n)
    {
        this->n = n;
        tree.resize(4 * n, 0);
    }

    void Add(int ind, long long val)
    {
        Adding(ind, val, 0, n, 0);
    }

    long long FindSum(int l, int r)
    {
        return Finding(l, r, 0, 0, n);
    }

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
        return Finding(l, mid, 2 * v + 1, tl, mid) + Finding(mid, r, 2 * v + 2, mid, tr);
    }

private:
    int n;
    vector<long long> tree;

};

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a[i];
    }

    SegmentTree tree_left(n);

    vector<long long> greater_on_left(n, 0);
    for (int i = 0; i < n; i++) {
        if (a[i] < n) {
            greater_on_left[i] = tree_left.FindSum(a[i], n); // [a[i], n)
        }
        tree_left.Add(a[i] - 1, 1);
    }

    SegmentTree tree_right(n);

    vector<long long> smaller_on_right(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > 1) {
            smaller_on_right[i] = tree_right.FindSum(0, a[i]); // [0, a[i])
        }
        tree_right.Add(a[i] - 1, 1);
    }

    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        total += greater_on_left[i] * smaller_on_right[i];
    }

    fout << total;

    return 0;
}