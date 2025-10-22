#include <iostream>
#include <fstream>
#include <vector>

#include "tree.hpp"

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree<long long> tree;

    long long temp;
    while (in >> temp)
    {
        tree.insert(temp);
    }

    vector<long long> result = tree.LeftPreOrderTraversal();

    for(long long value : result)
    {
        out << value << endl;
    }
    
    return 0;
}