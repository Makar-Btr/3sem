#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin ("input.txt");
    ofstream fout ("output.txt");

    int size;
    fin >> size;
    vector<long long> heap(size);
    for (int i = 0; i < size; i++)
    {
        fin >> heap[i];
    }

    for (int i = 0; i < size; i++)
    {
        if(i*2+1 < size && heap[i] > heap[i*2+1])
        {
            fout << "No";
            return 0;
        }

        if(i*2+2 < size && heap[i] > heap[i*2+2])
        {
            fout << "No";
            return 0;
        } 
    }

    fout << "Yes";

    return 0;
}