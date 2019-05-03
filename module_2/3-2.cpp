/*
 * Смирнова Анита АПО-12
 * Contest ID 20246151
 * Вычислить количество узлов в самом широком слое декартового дерева и количество узлов
 * в самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
 */
#include<iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <functional>

using std::cin;
using std::cout;

// functions common for BST and treap
template<class T>
int maxWidthTreap(T *root) {
    if (root == nullptr) {
        return 0;
    }
    std::queue<T *> q;
    q.push(root);
    int max_width = -1;
    int current_width = 1;
    while (!q.empty()) {
        for (int i = 0; i < current_width; i++) {
            T *node = q.front();
            q.pop();
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
        current_width = q.size();
        if (current_width > max_width) {
            max_width = current_width;
        }
    }
    return max_width;
}

template<class T>
void destroy_tree(T *root) {
    if (root) {
        destroy_tree(root->left);
        destroy_tree(root->right);
        delete (root);
    }
}

// TREAP
template<class T>
struct NodeTreap {
    T value;
    int priority;

    NodeTreap *left;
    NodeTreap *right;

    NodeTreap() : value(T()), priority(0), left(nullptr), right(nullptr) {}

    NodeTreap(T val, int priority, NodeTreap *left, NodeTreap *right) : value(val), priority(priority), left(left),
                                                                        right(right) {}
};

template<class T>
class Treap {
public:
    Treap();

    ~Treap();

    int width() const;

    void Insert(T key, int priority);

private:

    void insert(NodeTreap<T> *&currentNode, T key, int priority);

    void split(NodeTreap<T> *currentNode, T key, NodeTreap<T> *&left, NodeTreap<T> *&right);

    NodeTreap<T> *root;

};

template<class T>
Treap<T>::Treap() : root(nullptr) {}

template<class T>
Treap<T>::~Treap() {
    destroy_tree(root);
}

template<class T>
void Treap<T>::split(NodeTreap<T> *currentNode, T key, NodeTreap<T> *&left, NodeTreap<T> *&right) {
    if (currentNode == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (currentNode->value <= key) {
        split(currentNode->right, key, currentNode->right, right);
        left = currentNode;
    } else {
        split(currentNode->left, key, left, currentNode->left);
        right = currentNode;
    }
}

template<class T>
void Treap<T>::Insert(T key, int priority) {
    insert(root, key, priority);
}

template<class T>
void Treap<T>::insert(NodeTreap<T> *&currentNode, T key, int priority) {
    if (!currentNode) {
        currentNode = new NodeTreap<T>(key, priority, nullptr, nullptr);
        return;
    }
    if (currentNode->value <= key && currentNode->priority >= priority) {
        insert(currentNode->right, key, priority);
    } else if (currentNode->value > key && currentNode->priority >= priority) {
        insert(currentNode->left, key, priority);
    } else if (currentNode->priority < priority) {
        NodeTreap<T> *helper1 = nullptr;
        NodeTreap<T> *helper2 = nullptr;
        split(currentNode, key, helper1, helper2);
        auto *newNode = new NodeTreap<T>(key, priority, helper1, helper2);
        currentNode = newNode;
    }
}

template<class T>
int Treap<T>::width() const {
    return maxWidthTreap(root);
}

// BINARY TREE
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

    int width() const;

private:
    NodeBST<T> *root;
};

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
    destroy_tree(root);
}

template<class T>
int BinaryTree<T>::width() const {
    return maxWidthTreap(root);
}

int main() {
    int key = 0;
    int priority = 0;
    BinaryTree<int> myBtree;
    Treap<int> myTreap;
    int nodes_amount = 0;
    cin >> nodes_amount;
    for (int i = 0; i < nodes_amount; i++) {
        cin >> key >> priority;
        myBtree.Insert(key);
        myTreap.Insert(key, priority);
    }
    cout << myTreap.width() - myBtree.width() << "\n";
    return 0;
}
