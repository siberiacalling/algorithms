/*
 * Смирнова Анита АПО-12
 * Contest ID 20059843
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Выведите элементы в порядке in-order (слева направо).
 * Рекурсия запрещена.
 */
#include<iostream>
#include <fstream>
#include <queue>
#include <stack>

using std::cin;
using std::cout;

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    Node() : value(T()), left(nullptr), right(nullptr) {}

    explicit Node(const T &data) : value(data), left(nullptr), right(nullptr) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void Insert(const T &key);

    void inOrder();

private:
    void destroy_tree();

    Node<T> *root;

};

template<class T>
void BinaryTree<T>::inOrder() {
    std::stack<Node<T> *> s;
    Node<T> *current_node = root;
    while (current_node != nullptr || !s.empty()) {
        while (current_node != nullptr) {
            s.push(current_node);
            current_node = current_node->left;
        }
        current_node = s.top();
        s.pop();

        cout << current_node->value << " ";
        current_node = current_node->right;
    }
}

template<class T>
void BinaryTree<T>::Insert(const T &key) {
    Node<T> *current_root = root;
    Node<T> *node_to_insert = nullptr;

    while (current_root != nullptr) {
        node_to_insert = current_root;
        if (key < current_root->value)
            current_root = current_root->left;
        else
            current_root = current_root->right;
    }
    if (node_to_insert == nullptr) {
        root = new Node<T>(key);
    } else if (key < node_to_insert->value) {
        node_to_insert->left = new Node<T>(key);
    } else if (key > node_to_insert->value) {
        node_to_insert->right = new Node<T>(key);
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
    std::deque<Node<T> *> q;
    q.push_back(root);
    while (!q.empty()) {
        Node<T> *node = q.front();
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
    tree.inOrder();
    return 0;
}
