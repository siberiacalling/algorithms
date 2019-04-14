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

using std::cin;
using std::cout;

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    Node() : value(T()), left(nullptr), right(nullptr) {}
    Node(const T &data) : value(data), left(nullptr), right(nullptr) {}
    Node(const T &data, Node<T> *left, Node<T> *right) : value(data), left(left), right(right) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree();

    ~BinaryTree();

    void Insert(const T &key);

    void inOrder();

private:
    void destroy_tree(Node<T> *node);

    void insert(const T &key, Node<T> *node);

    void in_order(Node<T>* node);

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
void BinaryTree<T>::insert(const T &key, Node<T> *node) {
    if (key < node->value) {
        if (node->left != nullptr) {
            insert(key, node->left);
        } else {
            node->left = new Node<T>(key);
        }
    } else if (key > node->value){
        if (node->right != nullptr) {
            insert(key, node->right);
        } else {
            node->right = new Node<T>(key);
        }
    } else {
        return;
    }
}

template<class T>
void BinaryTree<T>::Insert(const T &key) {
    if (root == nullptr) {
        root = new Node<T>;
        root->value = key;
        root->right = nullptr;
        root->left = nullptr;
    } else {
        insert(key, root);
    }
}

template<class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<class T>
BinaryTree<T>::~BinaryTree() {
    destroy_tree(root);
}

template<class T>
void BinaryTree<T>::destroy_tree(Node<T> *node) {
    if (node != nullptr){
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete(node);
    }
}


int main() {
    int key = 0;
    BinaryTree<int> tree;
    //std::ifstream myfile{"/home/anita/Desktop/algorithms/module_2/test2.txt"};
    //while (myfile >> key) {
    while (cin >> key) {
        tree.Insert(key);
        //cout << key << "\n";
    }
    tree.inOrder();
    return 0;
}

