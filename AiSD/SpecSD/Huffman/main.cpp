#include <fstream>
#include <vector>

using namespace std;

long long Min(vector<long long>& frequencies, vector<long long>& nodes, int& i, int& j)
{
    if (i >= frequencies.size())
    {
        return nodes[j++];
    }
    else if (j >= nodes.size())
    {
        return frequencies[i++];
    }
    else if (frequencies[i] < nodes[j])
    {
        return frequencies[i++];
    }
    else
    {
        return nodes[j++];
    }
}

int main()
{
    ifstream fin ("huffman.in");
    ofstream fout ("huffman.out");

    int size;
    fin >> size;

    vector<long long> frequencies(size), nodes;
    for (int i = 0; i < size; ++i) 
    {
        fin >> frequencies[i];
    }

    int i = 0, j = 0;
    long long result = 0;

    long long u, v;
    while (size-- > 1)    
    {
        u = Min(frequencies, nodes, i, j);
        v = Min(frequencies, nodes, i, j);
        result += u + v;
        nodes.push_back(u + v);
    }

    fout << result << endl;

    return 0;
}