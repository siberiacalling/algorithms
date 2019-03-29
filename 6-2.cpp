#include <algorithm>
#include <iostream>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19792899
 * Найти k-ю порядковую статистику
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */

template<class T>
class CompareDefault {
public:
    bool operator()(const T &first, const T &second) const {
        return first > second;
    }
};

int medianThree(const int *arr, int left, int right) {
    int a = arr[right];
    int b = arr[left];
    int c = arr[(right - left) / 2 + left];
    int max = std::max(std::max(a, b), c);
    int min = std::min(std::min(a, b), c);
    int median = a + b + c - (min + max);
    if (median == a) {
        return right;
    }
    if (median == b) {
        return left;
    }
    return (right - left) / 2 + left;
}

template<class T, class Compare = CompareDefault<T>>
int partition(T *arr, int left, int right, Compare cmp) {
    int pivot_index = medianThree(arr, left, right);
    int pivot = arr[pivot_index];
    std::swap(arr[right], arr[pivot_index]);
    int i = left;
    int j = left;
    while (j != right) {
        if (cmp(arr[j], pivot)) {
            j++;
        } else {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[i], arr[j]);
    return i;
}

template<class T, class Compare = CompareDefault<T>>
int findKStat(T *arr, int array_length, int k, Compare cmp = Compare{}) {
    int left = 0;
    int right = array_length - 1;
    while (true) {
        int pivotPos = partition(arr, left, right, cmp);
        if (k == pivotPos) {
            return arr[k];
        }
        if (k < pivotPos) {
            right = pivotPos - 1;
        } else {
            left = pivotPos + 1;
        }
    }
}

int main() {
    int array_length = 0;
    int k = 0;
    std::cin >> array_length >> k;
    auto arr = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKStat(arr, array_length, k);
    delete[] arr;
    return 0;
}