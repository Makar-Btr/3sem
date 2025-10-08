#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Ward
{
    int number;
    int n;
    int a;
    int b;

    friend ifstream& operator>> (ifstream& in, Ward& obj)
    {
        in >> obj.n >> obj.a >> obj.b;
        return in;
    }

    friend bool operator> (Ward& x, Ward& y)
    {
        return x.n > y.n;
    }
};


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int a, b, p, total, inWard = 0;
    in >> a >> b >> p;

    total = a + b;
    if(total == 0)
    {
        out << 0;
        return 0;
    }

    vector<Ward> wards(p);
    for(int i = 0; i < p; i++)
    {
        wards[i].number = i + 1;
        in >> wards[i];
    }

    vector<int> wardsA;
    vector<Ward> emptyWards;

    for(int i = 0; i < p; i++)
    {
        if(wards[i].a > 0 && wards[i].b == 0)
        {
            inWard += min(a, wards[i].n - wards[i].a);
            a -= min(a, wards[i].n - wards[i].a);
            wardsA.push_back(i + 1);
        }
        else if(wards[i].a == 0 && wards[i].b > 0)
        {
            inWard += min(b, wards[i].n - wards[i].b);
            b -= min(b, wards[i].n - wards[i].b);
        }
        else if(wards[i].a == 0 && wards[i].b == 0)
        {
            emptyWards.push_back(wards[i]);
        }
    }

    sort(emptyWards.begin(), emptyWards.end(), [](Ward a, Ward b){ return a > b; });
    int free = 0, inEmptyWards = 0;
    int a1 = a, b1 = b;

    for(int i = 0; i < emptyWards.size(); i++)
    {
        free += emptyWards[i].n;
        if(a1 >= b1 && a1 > 0)
        {
            inEmptyWards += min(a1, emptyWards[i].n);
            a1 -= min(a1, emptyWards[i].n);
            wardsA.push_back(emptyWards[i].number);
        }
        else if(b1 > 0)
        {
            inEmptyWards += min(b1, emptyWards[i].n);
            b1 -= min(b1, emptyWards[i].n);
        }
    }
    
    inWard += min(free, inEmptyWards);
    sort(wardsA.begin(), wardsA.end());

    if(inWard == total)
    {
        out << inWard << endl;
        for(int i = 0; i < wardsA.size() - 1; i++)
        {
            out << wardsA[i] << " ";
        }
        out << wardsA[wardsA.size() - 1] << endl;
    }
    else
    {
        out << inWard << endl;
    }

    return 0;
}