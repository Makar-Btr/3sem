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

    int w_number, w_n, w_a, w_b;
    vector<int> wardsA;
    vector<Ward> emptyWards;
    for(int i = 0; i < p; i++)
    {
        w_number = i + 1;
        in >> w_n >> w_a >> w_b;

        if(w_a > 0 && w_b == 0)
        {
            inWard += min(a, w_n - w_a);
            a -= min(a, w_n - w_a);
            wardsA.push_back(i + 1);
        }
        else if(w_a == 0 && w_b > 0)
        {
            inWard += min(b, w_n - w_b);
            b -= min(b, w_n - w_b);
        }
        else if(w_n > 0 && w_a == 0 && w_b == 0)
        {
            emptyWards.push_back({w_number, w_n, w_a, w_b});
        }
    }

    if(emptyWards.empty())
    {
        out << inWard << endl;
        if(inWard == total && !wardsA.empty())
        {
            for(int i = 0; i < wardsA.size() - 1; i++)
            {
                out << wardsA[i] << " ";
            }
            out << wardsA[wardsA.size() - 1] << endl;
        }
        return 0;
    }

    int maxCap = 0;
    for (const Ward& ward : emptyWards)
    {
        maxCap += ward.n;
    }

    vector<vector<bool>> possibleSums(emptyWards.size() + 1, vector<bool>(maxCap + 1, false));
    possibleSums[0][0] = true;
    int cap;
    for(int i = 1; i <= emptyWards.size(); i++)
    {
        cap = emptyWards[i - 1].n;
        for(int j = 0; j <= maxCap; j++)
        {
            possibleSums[i][j] = possibleSums[i - 1][j];
            if(j >= cap && possibleSums[i - 1][j - cap])
            {
                possibleSums[i][j] = true;
            }
        }
    }

    int placedInEmpty = -1, bestA = -1;
    int plasedA, plasedB;
    for(int s = 0; s <= maxCap; s++)
    {
        if(possibleSums[emptyWards.size()][s])
        {
            plasedA = min(a, s);
            plasedB = min(b, maxCap - s);
        }
        if(placedInEmpty < plasedA + plasedB)
        {
            placedInEmpty = plasedA + plasedB;
            bestA = s;
        }
    }

    out << inWard + placedInEmpty << endl;

    if(inWard + placedInEmpty == total)
    {
        int sum = bestA;
        for(int s = emptyWards.size(); s > 0; s--)
        {
            cap = emptyWards[s - 1].n;
            if(sum >= cap && possibleSums[s - 1][sum - cap])
            {
                wardsA.push_back(emptyWards[s - 1].number);
                sum -= cap;
            }
        }

        sort(wardsA.begin(), wardsA.end());

        if(!wardsA.empty())
        {
            for(int s = 0; s < wardsA.size() - 1; s++)
            {
                out << wardsA[s] << " ";
            }
            out << wardsA[wardsA.size() - 1] << endl;
        }
    }


    return 0;
}