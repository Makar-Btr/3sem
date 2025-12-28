/*По набору ключей постройте бинарное поисковое дерево и выполните его прямой
левый обход.

Input
Входной файл содержит последовательность чисел — ключи вершин в порядке
добавления в дерево. Ключи задаются в формате по одному в строке. В поисковом
дереве все ключи по определению уникальны, поэтому при попытке добавить в дерево
ключ, который там уже есть, он игнорируется.

Output
Выходной файл должен содержать последовательность ключей вершин, полученную
прямым левым обходом дерева.*/

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