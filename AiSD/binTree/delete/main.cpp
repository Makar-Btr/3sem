#include <fstream>
#include <vector>

#include "tree.hpp"

using namespace std;

#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree<long long> tree;

    long long valueToDelete;
    in >> valueToDelete;
    
    long long temp;
    while (in >> temp)
    {
        tree.insert(temp);
    }

    tree.removeRight(valueToDelete);

    vector<long long> result = tree.LeftPreOrderTraversal();

    for(long long value : result)
    {
        out << value << endl;
    }
    
    return 0;
}