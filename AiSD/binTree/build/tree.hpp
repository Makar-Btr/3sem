#include <vector>

using namespace std;

template<class T>
class Tree
{

public:
    
    Tree() : m_root(nullptr) {};

    void insert(T value)
    {
        m_root = insertion(m_root, value);
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

    vector<T> LeftPostOrderTraversal()
    {
        vector<T> result;

        LeftPostOrder(m_root, result);

        return result;
    }

    vector<T> RightPostOrderTraversal()
    {
        vector<T> result;

        RightPostOrder(m_root, result);

        return result;
    }

    vector<T> LeftInOrderTraversal()
    {
        vector<T> result;

        LeftInOrder(m_root, result);

        return result;
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
    
    Node* insertion(Node* node, int key) 
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

    void LeftPostOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            LeftPostOrder(node->m_left, result);
            LeftPostOrder(node->m_right, result);
            result.push_back(node->m_value);
        }
    }

    void RightPostOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            RightPostOrder(node->m_right, result);
            RightPostOrder(node->m_left, result);
            result.push_back(node->m_value);
        }
    }

    void LeftInOrder(Node* node, vector<T>& result)
    {
        if (node != nullptr) 
        {
            LeftInOrder(node->m_left, result);
            result.push_back(node->m_value);
            LeftInOrder(node->m_right, result);
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

        Node(T value) : m_value(value), m_left(nullptr), m_right(nullptr) {};
    };
    Node* m_root;

};