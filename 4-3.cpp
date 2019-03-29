#include <iostream>
#include <queue>
#include <utility>
#include <assert.h>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19792899
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 * Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления.
 * Напишите программу, которая по данному расписанию определяет,
 * какое минимальное количество тупиков требуется для работы вокзала.
 */

template<class T>
class CompareDefault {
public:
    bool operator()(const T &time1, const T &time2) const {
        return time1 < time2;
    }
};

class ComparePair {
public:
    bool operator()(const std::pair<int, int> &time1, const std::pair<int, int> &time2) const {
        return time1.second < time2.second;
    }
};

template<class T, class Compare = CompareDefault<T>>
class Heap {
public:
    Heap();

    ~Heap();

    void push(const T &item);

    T pop();

    const T& top() const;

    bool isEmpty() const;

    int size() const;

private:
    void SiftUp(int i);

    void SiftDown(int index);

    const int buffer_size;
    const Compare cmp;

    int elements_amount;
    T *elements;
};

template<class T, class Compare>
Heap<T, Compare>::Heap()
        : buffer_size(256), cmp(), elements_amount(0) {
    elements = new T[buffer_size];
}

template<class T, class Compare>
Heap<T, Compare>::~Heap() {
    delete[] elements;
}

template<class T, class Compare>
bool Heap<T, Compare>::isEmpty() const {
    return elements_amount == 0;
}

template<class T, class Compare>
void Heap<T, Compare>::push(const T &item) {
    elements[elements_amount] = item;
    elements_amount++;
    SiftUp(elements_amount - 1);
}

template<class T, class Compare>
int Heap<T, Compare>::size() const {
    return elements_amount;
}

template<class T, class Compare>
T Heap<T, Compare>::pop() {
    assert(!isEmpty());
    T result = elements[0];

    std::swap(elements[0], elements[elements_amount - 1]);
    elements_amount--;

    if (!isEmpty()) {
        SiftDown(0);
    }
    return result;
}

template<class T, class Compare>
const T& Heap<T, Compare>::top() const {
    assert(!isEmpty());
    return elements[0];
}

template<class T, class Compare>
void Heap<T, Compare>::SiftUp(const int index) {
    int i = index;
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (!cmp(elements[i], elements[parent])) {
            return;
        }
        std::swap(elements[i], elements[parent]);
        i = parent;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::SiftDown(const int i) {
    const int left = 2 * i + 1;
    const int right = 2 * i + 2;

    int largest = i;
    if (left < elements_amount && cmp(elements[left], elements[i]))
        largest = left;
    if (right < elements_amount && cmp(elements[right], elements[largest]))
        largest = right;

    if (largest != i) {
        std::swap(elements[i], elements[largest]);
        SiftDown(largest);
    }
}


int main() {
    Heap<std::pair<int, int>, ComparePair> myQueue;

    int trains_amount = 0;
    std::cin >> trains_amount;

    for (int i = 0; i < trains_amount; i++) {
        int arrival_time = 0, departure_time = 0;
        std::cin >> arrival_time >> departure_time;
        if (myQueue.isEmpty()) {
            myQueue.push({arrival_time, departure_time});
        } else {
            if (myQueue.top().second < arrival_time) {
                myQueue.pop();
            }
            myQueue.push({arrival_time, departure_time});
        }
    }
    std::cout << myQueue.size();
    return 0;
}