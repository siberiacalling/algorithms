/*
 * Смирнова Анита АПО-12
 * Contest ID
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Выведите элементы в порядке in-order (слева направо).
 * Рекурсия запрещена.
 */
#include<iostream>
#include <fstream>
#include <queue>

using std::cin;
using std::cout;

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    Node() : value(T()), left(nullptr), right(nullptr) {}

    Node(const T &data) : value(data), left(nullptr), right(nullptr) {}

    //Node(const T &data, Node<T> *left, Node<T> *right) : value(data), left(left), right(right) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void Insert(const T &key);

    void inOrder();

private:
    void round_tree(Node<T> *root);

    void destroy_tree();

    void in_order(Node<T> *node);

    Node<T> *root;

};

template<class T>
void BinaryTree<T>::in_order(Node<T> *node) {
    if (!node)
        return;

    in_order(node->left);
    cout << node->value << " ";
    in_order(node->right);

}

template<class T>
void BinaryTree<T>::inOrder() {
    in_order(root);
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

template<class T>
void BinaryTree<T>::round_tree(Node<T> *root) {
    if (root == nullptr) {
        return;
    }
    std::deque<Node<T> *> q;
    q.put(root);
    while (!q.empty()) {
        Node<T> *node = q.front();
        //visit(node);
        if (node->Left != nullptr)
            q.push(node->Left);
        if (node->Right != nullptr)
            q.push(node->Right);
    }
}

int main() {
    int key = 0;
    BinaryTree<int> tree;
    // std::ifstream myfile{"/home/anita/Desktop/algorithms/module_2/test2.txt"};
    while (cin >> key) {
        tree.Insert(key);
        //cout << key << "\n";
    }
    tree.inOrder();
    return 0;
}
