/*
 * Смирнова Анита АПО-12
 * Contest ID 20238842
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Выведите элементы в порядке in-order (слева направо).
 * Рекурсия запрещена.
 */
#include<iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <functional>

using std::cin;
using std::cout;

template<class T>
struct NodeBST {
    T value;
    NodeBST *left;
    NodeBST *right;

    NodeBST() : value(T()), left(nullptr), right(nullptr) {}

    explicit NodeBST(const T &data) : value(data), left(nullptr), right(nullptr) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void Insert(const T &key);

    void inOrder(std::function<void(T)> callback);

private:
    void destroy_tree();

    NodeBST<T> *root;

};

template<class T>
void BinaryTree<T>::inOrder(std::function<void(T)> callback) {
    std::stack<NodeBST<T> *> s;
    NodeBST<T> *current_node = root;
    while (current_node != nullptr || !s.empty()) {
        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }
        current_node = s.top();
        s.pop();

        callback(current_node->value);
        current_node = current_node->right;
    }
}

template<class T>
void BinaryTree<T>::Insert(const T &key) {
    NodeBST<T> *current_root = root;
    NodeBST<T> *node_to_insert = nullptr;

    while (current_root != nullptr) {
        node_to_insert = current_root;
        if (key < current_root->value)
            current_root = current_root->left;
        else
            current_root = current_root->right;
    }
    if (node_to_insert == nullptr) {
        root = new NodeBST<T>(key);
    } else if (key < node_to_insert->value) {
        node_to_insert->left = new NodeBST<T>(key);
    } else if (key > node_to_insert->value) {
        node_to_insert->right = new NodeBST<T>(key);
    } else {
        return;
    }
}

template<class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<class T>
BinaryTree<T>::~BinaryTree() {
    destroy_tree();
}

template<class T>
void BinaryTree<T>::destroy_tree() {
    if (root == nullptr) {
        return;
    }
    std::deque<NodeBST<T> *> q;
    q.push_back(root);
    while (!q.empty()) {
        NodeBST<T> *node = q.front();
        if (node->left != nullptr)
            q.push_back(node->left);
        if (node->right != nullptr)
            q.push_back(node->right);
        q.pop_front();
        delete (node);
    }
}

int main() {
    int key = 0;
    BinaryTree<int> tree;
    while (cin >> key) {
        tree.Insert(key);
    }
    tree.inOrder([](int value) {
        cout << value << " ";
    });
    return 0;
}
