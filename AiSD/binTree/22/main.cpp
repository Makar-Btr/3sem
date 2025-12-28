/*Найти среднюю из вершин дерева, у которых высоты поддеревьев не равны, а число
потомков в правом и левом поддеревьях совпадает. Удалить её (правым удалением),
если такая вершина существует.

Если у вершины отсутствует некоторое поддерево, то его высоту полагаем равной
−1, а число вершин этого поддерева — 0.

Input
Входной файл содержит последовательность чисел — ключи вершин в порядке
добавления в дерево. 

Output 
Выходной файл должен содержать последовательность
ключей вершин, полученную прямым левым обходом итогового дерева.*/

#include <fstream>
#include <vector>

using namespace std;

template<class T>
class Tree
{
public:
    
    Tree() : m_root(nullptr), m_candidatCount(0) {};

    void Solve(ofstream &fout)
    {
        m_candidatCount = 0;
        LeftPostOrderTraversal();

        if(m_candidatCount > 0 && m_candidatCount % 2 != 0)
        {
            m_candidatCount = (m_candidatCount + 1) / 2;

            LeftInOrder(m_root);
        }

        for(long long value : LeftPreOrderTraversal())
        {
            fout << value << endl;
        }
    }

    void insert(T value)
    {
        m_root = insertion(m_root, value);
    }

    void removeRight(T value)
    {
        m_root = rightRemoval(m_root, value);
    }

    void removeLeft(T value)
    {
        m_root = leftRemoval(m_root, value);
    }

    vector<T> LeftPreOrderTraversal()
    {
        vector<T> result;

        LeftPreOrder(m_root, result);

        return result;
    }

    vector<T> RightPreOrderTraversal()
    {
        vector<T> result;

        RightPreOrder(m_root, result);

        return result;
    }

    void LeftPostOrderTraversal()
    {
        LeftPostOrder(m_root);
    }

    void RightPostOrderTraversal()
    {
        RightPostOrder(m_root);
    }

    void LeftInOrderTraversal()
    {

        LeftInOrder(m_root);

    }

    vector<T> RightInOrderTraversal()
    {
        vector<T> result;

        RightInOrder(m_root, result);

        return result;
    }

    ~Tree()
    {
        deleteTree(m_root);
    }

private:

    struct Node;
    
    Node* insertion(Node* node, T key) 
    {
        if(node == nullptr) 
        {
            return new Node(key);
        }
        
        if(key < node->m_value) 
        {
            node->m_left = insertion(node->m_left, key);
        } 
        else if(key > node->m_value)
        {
            node->m_right = insertion(node->m_right, key);
        }
        
        return node;
    }

    Node* findMin(Node* node)
    {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->m_left != nullptr) {
            node = node->m_left;
        }
        return node;
    }

    Node* rightRemoval(Node* node, T key)
    {
        if (node == nullptr) 
        {
            return nullptr; 
        }

        if (key < node->m_value) 
        {
            node->m_left = rightRemoval(node->m_left, key);
        } 
        else if (key > node->m_value) 
        {
            node->m_right = rightRemoval(node->m_right, key);
        }
        else 
        {
            if (node->m_left == nullptr && node->m_right == nullptr) 
            {
                delete node;
                return nullptr;
            }
            else if (node->m_left == nullptr) 
            {
                Node* temp = node->m_right;
                delete node;
                return temp;
            }
            else if (node->m_right == nullptr) 
            {
                Node* temp = node->m_left;
                delete node;
                return temp;
            }
            else 
            {
                Node* successor = findMin(node->m_right);
                
                node->m_value = successor->m_value;
                
                node->m_right = rightRemoval(node->m_right, successor->m_value);
            }
        }
        return node;
    }

    Node* findMax(Node* node)
    {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->m_right != nullptr) {
            node = node->m_right;
        }
        return node;
    }

    Node* leftRemoval(Node* node, T key)
    {
        if (node == nullptr) 
        {
            return nullptr; 
        }
        if (key < node->m_value) 
        {
            node->m_left = leftRemoval(node->m_left, key);
        } 
        else if (key > node->m_value) 
        {
            node->m_right = leftRemoval(node->m_right, key);
        }
        else 
        {
            if (node->m_left == nullptr && node->m_right == nullptr) 
            {
                delete node;
                return nullptr;
            }
            else if (node->m_left == nullptr) 
            {
                Node* temp = node->m_right;
                delete node;
                return temp;
            }
            else if (node->m_right == nullptr) 
            {
                Node* temp = node->m_left;
                delete node;
                return temp;
            }
            else 
            {
                Node* predecessor = findMax(node->m_left);
                
                node->m_value = predecessor->m_value;
                
                node->m_left = leftRemoval(node->m_left, predecessor->m_value);
            }
        }
        return node;
    }

    void LeftPreOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            result.push_back(node->m_value);
            LeftPreOrder(node->m_left, result);
            LeftPreOrder(node->m_right, result);
        }
    }

    void RightPreOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            result.push_back(node->m_value);
            RightPreOrder(node->m_right, result);
            RightPreOrder(node->m_left, result);
        }
    }

    pair<int, int> LeftPostOrder(Node* node)
    {
        if (node == nullptr) 
        {
            return {-1, 0};
        }
        pair<int, int> left = LeftPostOrder(node->m_left);
        pair<int, int> right = LeftPostOrder(node->m_right);
            
        if(right.first != left.first && right.second == left.second)
        {
            node->m_isCandidat = true;
            m_candidatCount++;
        }
        else
        {
            node->m_isCandidat = false;
        }
        return {max(right.first, left.first) + 1, right.second + left.second + 1};
        
    }

    pair<int, int> RightPostOrder(Node* node)
    {
        if (node == nullptr) 
        {
            return {-1, 0};
        }

        pair<int, int> right = RightPostOrder(node->m_right);
        pair<int, int> left = RightPostOrder(node->m_left);

        if(right.first != left.first && right.second == left.second)
        {
            node->m_isCandidat = true;
            m_candidatCount++;
        }
        else
        {
            node->m_isCandidat = false;
        }
        
        return {max(right.first, left.first) + 1, right.second + left.second + 1};
    }

    void LeftInOrder(Node* node)
    {
        if (node != nullptr) 
        {
            LeftInOrder(node->m_left);
            if(node->m_isCandidat)
            {
                m_candidatCount--;
                if(m_candidatCount == 0)
                {
                    rightRemoval(m_root, node->m_value);
                    return;
                }
                
            }
            LeftInOrder(node->m_right);
        }
    }

    void RightInOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            RightInOrder(node->m_right, result);
            result.push_back(node->m_value);
            RightInOrder(node->m_left, result);
        }
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->m_left);
            deleteTree(node->m_right);
            delete node;
        }
    }

private:
    struct Node
    {
        T m_value;
        Node* m_left;
        Node* m_right;
        bool m_isCandidat;


        Node(T value) : m_value(value), m_left(nullptr), m_right(nullptr), m_isCandidat(false) {};
    };
    Node* m_root;
    int m_candidatCount;

};

int main()
{
    ios_base::sync_with_stdio(false);

    ifstream fin("in.txt");
    ofstream fout("out.txt");

    Tree<long long> tree;
    
    long long temp;
    while (fin >> temp)
    {
        tree.insert(temp);
    }

    tree.Solve(fout);
    
    return 0;
}