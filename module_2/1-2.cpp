#include<vector>
#include<string>
#include<assert.h>
#include<iostream>
#include <fstream>
#include <limits>

using std::vector;
using std::string;
using std::cin;
using std::cout;

const int DefaultHashTableSize = 2;
const float MaxAlpha = 0.79;
const int GrowFactor = 2;


std::uint32_t hash1(const string &key) {
    std::uint32_t hash = 0;
    for (char i : key)
        hash = (hash * (std::uint32_t) 127 + (std::uint32_t) i);
    return hash;
}

std::uint32_t hash2(const string &key) {
    std::uint32_t hash = 5381;
    for (auto i : key) {
        hash = (hash << (std::uint32_t) 5) + hash + (std::uint32_t) i;
    }
    if (hash == std::numeric_limits<uint32_t>::max()) {
        return 1;
    }
    return hash + 1;
}

template<class T>
struct HashTableNode {
    T data;
    enum class Status {
        EMPTY, DELETED, INSERTED
    };
    Status status;

    HashTableNode() : data(T()), status(Status::EMPTY) {}

    explicit HashTableNode(const T &data) : data(data), status(Status::INSERTED) {}
};

template<class T>
class HashTable {
public:
    HashTable();

    bool Has(const T &key) const;

    bool Add(const T &key);

    bool Delete(const T &key);

    void displayHash();

private:

    vector<HashTableNode<T>> table;
    int keysCount;

    bool has(std::uint64_t h1, std::uint64_t h2, const T &key) const;

    void growTable();
};

template<class T>
HashTable<T>::HashTable() : keysCount(0) {
    table.resize(DefaultHashTableSize);
}

template<class T>
void HashTable<T>::growTable() {
    vector<HashTableNode<T>> tableCopy = table;
    vector<HashTableNode<T>> newTable(table.size() * GrowFactor);
    table = newTable;
    for (int i = 0; i < (int) tableCopy.size(); i++) {
        Add(tableCopy[i].data);
    }
}

template<class T>
bool HashTable<T>::Add(const T &key) {
    std::uint64_t x = hash1(key);
    std::uint64_t y = hash2(key);


    if (Has(key)) {
        return false;
    }

    for (int i = 0; i < (int) table.size(); i++) {
        x = x + i * y;
        int index = x % table.size();
        if (table[index].status != HashTableNode<T>::Status::INSERTED) {
            table[index] = HashTableNode<T>(key);
            keysCount++;
            if ((float)keysCount / (float)table.size() >= MaxAlpha) {
                growTable();
            }
            return true;
        }
    }
    growTable();
    return Add(key);
}

template<class T>
bool HashTable<T>::Delete(const T &key) {
    std::uint64_t h1 = hash1(key);
    std::uint32_t h2 = hash2(key);
    for (int i = 0; i < (int) table.size(); i++) {
        h1 = h1 + i * h2;
        int index = h1 % table.size();
        if (table[index].status == HashTableNode<T>::Status::INSERTED && table[index].data == key) {
            table[index].status = HashTableNode<T>::Status::DELETED;
            keysCount--;
            return true;
        }
        if (table[index].status == HashTableNode<T>::Status::EMPTY) {
            return false;
        }
    }
    return false;
}

template<class T>
bool HashTable<T>::Has(const T &key) const {
    std::uint64_t h1 = hash1(key);
    std::uint64_t h2 = hash2(key);
    return has(h1, h2, key);
}

template<class T>
bool HashTable<T>::has(std::uint64_t h1, std::uint64_t h2, const T &key) const {
    for (int i = 0; i < (int) table.size(); i++) {
        h1 = h1 + i * h2;
        int index = h1 % table.size();
        if (table[index].status == HashTableNode<T>::Status::INSERTED && table[index].data == key) {
            return true;
        }
        if (table[index].status == HashTableNode<T>::Status::EMPTY) {
            return false;
        }
    }
    return false;
}

template<class T>
void HashTable<T>::displayHash() {
    for (int i = 0; i < (int) table.size(); i++) {
        if (table[i].status == HashTableNode<T>::Status::INSERTED)
            cout << i << " --> " << table[i].Data << " " << (int) table[i].status << std::endl;
        else
            cout << i << std::endl;
    }
}

int main() {
    HashTable<string> table;
    char command = 0;
    string key;

    while (cin >> command >> key) {
        switch (command) {
            case '+':
                cout << (table.Add(key) ? "OK" : "FAIL") << "\n";
                break;
            case '-':
                //table.displayHash();
                cout << (table.Delete(key) ? "OK" : "FAIL") << "\n";
                break;
            case '?':
                cout << (table.Has(key) ? "OK" : "FAIL") << "\n";
                break;
            default:
                assert(false);
        }
    }
    return 0;
}