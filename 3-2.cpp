#include <vector>
#include <iostream>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19640178
 * Реализовать дек с динамическим зацикленным буфером.
 * Обрабатывать команды push * и pop *.
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Если дана команда pop *, то число b - ожидаемое значение.
 * Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”
 */

template<class T>
class Deque {
public:
    Deque();

    // adds item to front of Deque
    void pushFront(T item);

    // adds item to back of Deque
    void pushBack(T item);

    // removes item from front of Deque
    T popFront();

    // removes item from back of Deque
    T popBack();

    // are there any elements in the Deque
    bool isEmpty() const;

    std::vector<T> increaseVectorSize();

private:
    int front;
    int back;
    int buffer_size;
    int elements_amount;
    std::vector<T> elements;

};

template<class T>
Deque<T>::Deque()
        : buffer_size(4), front(-1), back(-1), elements_amount(0) {
    elements.resize(static_cast<unsigned long>(buffer_size));
}

template<class T>
bool Deque<T>::isEmpty() const { // O(1) time, O(1) memory
    return elements_amount == 0;
}

template<class T>
std::vector<T> Deque<T>::increaseVectorSize() { // O(n) time, O(n) memory
    buffer_size *= 2;
    std::vector<T> new_elements(static_cast<unsigned long>(buffer_size));
    int j = front;
    for (int i = 0; i < elements_amount; i++) {
        new_elements[i] = elements[front];
        front = (front + 1) % elements_amount;
    }
    front = 0;
    back = buffer_size / 2 - 1;
    return new_elements;
}

template<class T>
T Deque<T>::popBack() { // O(1) time, O(1) memory
    if (isEmpty()) {
        return -1;
    }

    T last_elem = elements[back];

    // pop last element in Deque
    if (elements_amount == 1) {
        front = -1;
        back = -1;
    }
    // back points to the first element
    else if (back == 0) {
        back = buffer_size - 1;
    } else {
        back = back - 1;
    }
    elements_amount--;

    return last_elem;
}

template<class T>
T Deque<T>::popFront() { // O(1) time, O(1) memory
    if (isEmpty()) {
        return -1;
    }

    T first_elem = elements[front];

    // pop last element in Deque
    if (elements_amount == 1) {
        front = -1;
        back = -1;
    }
    // front points to the last element
    else if (front == buffer_size - 1) {
        front = 0;
    } else {
        front = front + 1;
    }
    elements_amount--;
    return first_elem;
}

template<class T>
void Deque<T>::pushBack(const T item) { // O(1) time (amortized), O(1) memory (amortized)
    int next_back = 0;

    // if Deque is empty
    if (isEmpty()) {
        next_back = 0;
        front = 0;
    }
        // back points to the last element
    else if (back == buffer_size - 1) {
        next_back = 0;
    } else {
        next_back = back + 1;
    }

    // if Deque is full
    if (elements_amount == buffer_size) {
        elements = increaseVectorSize();
        next_back = back + 1;
    }
    back = next_back;
    elements[back] = item;
    elements_amount++;
}

template<class T>
void Deque<T>::pushFront(const T item) { // O(1) time (amortized), O(1) memory (amortized)
    int next_front = 0;

    // if Deque is empty
    if (isEmpty()) {
        next_front = 0;
        back = 0;
    }
    // front points to the first element
    else if (front == 0) {
        next_front = buffer_size - 1;
    } else {
        next_front = front - 1;
    }

    // if Deque is full
    if (elements_amount == buffer_size) {
        elements = increaseVectorSize();
        next_front = buffer_size - 1;
    }
    front = next_front;
    elements[next_front] = item;
    elements_amount++;
}

int main() {
    Deque<int> deque;
    int commands_amount = 0;
    std::cin >> commands_amount;
    bool result = true;
    for (int i = 0; i < commands_amount; i++) {
        int command = 0;
        int data = 0;
        std::cin >> command >> data;
        switch (command) {
            case 1:
                deque.pushFront(data);
                break;
            case 2:
                if (deque.isEmpty()) {
                    result = result && data == -1;
                } else {
                    result = result && deque.popFront() == data;
                }
                break;
            case 3:
                deque.pushBack(data);
                break;
            case 4:
                if (deque.isEmpty()) {
                    result = result && data == -1;
                } else {
                    result = result && deque.popBack() == data;
                }
                break;
            default:
                break;
        }
    }
    if (result) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}