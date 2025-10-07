#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int i = 0, temp;
    long long sum = 0;
    vector<int> vec;
    while(!in.eof())
    {
        in >> temp;
        vec.push_back(temp);
    }
    in.close();

    sort(vec.begin(), vec.end(), [](int a, int b){ return a < b; });

    i = 0;
    while(i < vec.size() - 1)
    {
        if(vec[i] != vec[i + 1])
        {
            sum += vec[i];
        }
        i++;
    }
    sum += vec[vec.size() - 1];
    out << sum;
    
    out.close();
    
    return 0;
}
