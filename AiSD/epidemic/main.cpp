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
        in >> wards[i].n >> wards[i].a >> wards[i].b;
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

    sort(emptyWards.begin(), emptyWards.end(), [](Ward a, Ward b){ return a.n > b.n; });

    for(int i = 0; i < emptyWards.size(); i++)
    {
        if(a == 0 && b == 0)
        {
            break;
        }

        if(a >= b && a > 0)
        {
            inWard += min(a, emptyWards[i].n);
            a -= min(a, emptyWards[i].n);
            wardsA.push_back(emptyWards[i].number);
        }
        else if(b > a && b > 0)
        {
            inWard += min(b, emptyWards[i].n);
            b -= min(b, emptyWards[i].n);
        }
        else if(a > 0)  // a == b или b == 0
        {
            int canPlace = min(a, emptyWards[i].n);
            inWard += canPlace;
            a -= canPlace;
            wardsA.push_back(emptyWards[i].number);
        }
        else if(b > 0)  // a == 0
        {
            int canPlace = min(b, emptyWards[i].n);
            inWard += canPlace;
            b -= canPlace;
        }
    }
    
    sort(wardsA.begin(), wardsA.end());

    if(inWard == total)
    {
        out << inWard << endl;
        if(!wardsA.empty())
        {
            for(int i = 0; i < wardsA.size() - 1; i++)
            {
                out << wardsA[i] << " ";
            }
            out << wardsA[wardsA.size() - 1] << endl;
        }
    }
    else
    {
        out << inWard << endl;
    }

    return 0;
}