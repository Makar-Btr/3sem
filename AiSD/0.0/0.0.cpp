/*Дано бинарное поисковое дерево, в котором ключи вершин являются целыми числами
в диапазоне от −231 до 231 − 1 включительно. Найдите сумму ключей всех вершин
дерева.

Input
Входной файл содержит последовательность чисел — ключи вершин в порядке
добавления в дерево. Ключи задаются в формате по одному в строке. В поисковом
дереве все ключи по определению уникальны, поэтому при попытке добавить в дерево
ключ, который там уже есть, он игнорируется.

Output
Выведите единственное число — сумму ключей в построенном дереве.*/

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
