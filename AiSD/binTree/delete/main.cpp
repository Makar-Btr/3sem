/*По набору ключей постройте бинарное поисковое дерево. Удалите из него ключ
(правым удалением), если он есть в дереве. Выполните прямой левый обход
полученного дерева.

Input
В первой строке записано целое число — ключ, который нужно удалить из дерева.
Вторая строка пустая.

Последующие строки содержат последовательность чисел — ключи вершин в порядке
добавления в дерево. Ключи задаются в формате по одному в строке. Дерево
содержит хотя бы две вершины.

Напомним, что в поисковом дереве все ключи по определению уникальны, поэтому при
попытке добавить в дерево ключ, который там уже есть, он игнорируется.

Output
Выведите последовательность ключей вершин, полученную прямым левым обходом
дерева.*/

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