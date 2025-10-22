#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("bst.in");
    ofstream out("bst.out");

    int size;
    in >> size;

    vector<int> values(size + 1); 
    vector<pair<long long, long long>> intervals(size + 1);

    in >> values[1];
    intervals[1].first = INT_MIN;
    intervals[1].second = (long long)INT_MAX + 1;

    int parent;
    char place;
    for (int i = 2; i <= size; ++i)
    {
        in >> values[i] >> parent >> place;


        if (place == 'L')
        {
            intervals[i].first = intervals[parent].first;
            intervals[i].second = values[parent];
        }
        else
        {
            intervals[i].first = values[parent];
            intervals[i].second = intervals[parent].second;
        }

        if (!((long long)values[i] >= intervals[i].first && (long long)values[i] < intervals[i].second))
        {
            out << "NO" << endl;
            return 0;
        }
    }

    out << "YES" << endl;
    
    return 0;
}