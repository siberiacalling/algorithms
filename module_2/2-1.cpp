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
    struct Node *left;
    struct Node *right;

    Node() : value(T()), left(nullptr), right(nullptr) {}

    Node(const T &data, Node<T> *left, Node<T> *right) : value(data), left(left), right(right) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree();


    void Insert(const T &key);

    // void destroyTree();

private:
    //void destroyTree(Node<T> *leaf);

    void insert(const T &key, Node<T> *root);

    Node<T> *root;

};

template<class T>
void BinaryTree<T>::insert(const T &key, Node<T> *sheet) {
    if (key < sheet->value) {
        if (sheet->left != nullptr) {
            insert(key, sheet->left);
        } else {
            sheet->left = new Node<T>;
            sheet->left->value = key;
            sheet->left->left = nullptr;
            sheet->left->right = nullptr;
        }
    } else {
        if (sheet->right != nullptr) {
            insert(key, sheet->left);
        } else {
            sheet->left = new Node<T>;
            sheet->left->value = key;
            sheet->left->left = nullptr;
            sheet->left->right = nullptr;
        }
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


int main() {
    int key = 0;
    BinaryTree<int> tree;
    std::ifstream myfile{"/home/anita/Desktop/algorithms/module_2/test2.txt"};
    while (myfile >> key) {
        tree.Insert(key);
        cout << key << "\n";
    }
    return 0;
}

