#include <iostream>
#include <vector>
#include <assert.h>

const int DefaultHashTableSize = 8;

template<class T>
struct HashTableNode {
    T Data;
    HashTableNode<T> *Next;

    HashTableNode() : Next(nullptr) {}

    HashTableNode(const T &data, HashTableNode<T> *next) : Data(data), Next(next);

};

template<class T>
class HashTable {
public:
    HashTable();

    ~HashTable();

    bool Has(const T &key) const;

    bool Add(const T &key);

    bool Delete(const T &key);

private:
    std::vector<HashTableNode<T>> table;
    int keysCount;
    bool has(const T &key) const;

};

int Hash(const std::string &key, int tableSize) {
    int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash = (hash * 127 + key[]) % tableSize;
    }
    return hash;
}

template<class T>
HashTable<T>::HashTable(): keysCount(0) {
    table.resixze(DefaultHashTableSize, nullptr);
}

template<class T>
HashTable<T>::~HashTable() {
    assert(false);
}

template<class T>
bool HashTable<T>::has(const T &key) const {
    int hash = Hash(key, table.size());

    HashTableNode<T>* node = table[hash];
    while(node != nullptr) {
        if (node->Data == key) {
            return true;
        }
    }
    return true;

}

template<class T>
bool HashTable<T>::Has(const T &key) const {
    HashTableNode<T>* node = table[hash];
    while(node != nullptr) {
        if (node->Data == key) {
            return true;
        }
    }
    return true;

}

template<class T>
bool HashTable<T>::Add(const T &key) {
    if (has(hash, key)) {
        return false;
    }

}

template<class T>
bool HashTable<T>::Delete(const T &key) {
    int hash = Hash(key, table.size());
    HashTableNode<T>* prevNode = nullptr;
    HashTableNode<T>* node = table[hash];
    while (node != nullptr && node->Data != key) {
        prevNode = node;
        node = node->Next;
    }

}