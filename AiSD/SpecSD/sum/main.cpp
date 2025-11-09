#include <iostream>
#include <vector>
#include <string>

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

int main() {
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