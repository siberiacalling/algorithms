/*
 * Найти k-ю порядковую статистику
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */


#include <algorithm>
#include <iostream>

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

void print_arr(int *arr, int left, int right) {
    for (int i = left; i < right; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}


int partition(int *arr, int left, int right) {
    int pivot_index = medianThree(arr, left, right);
    int pivot = arr[pivot_index];
    std::swap(arr[right], arr[pivot_index]);
    int i = left;
    int j = left;
    while (j != right) {
        if (arr[j] > pivot) {
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

int findKStat(int *arr, int array_length, int k) {
    int left = 0;
    int right = array_length - 1;
    while (true) {
        int pivotPos = partition(arr, left, right);
        if (k == pivotPos) {
            return arr[k];
        }
        if (k < pivotPos) {
            right = pivotPos;
        } else {
            left = pivotPos + 1;
        }
    }
}

int main() {
    int array_length = 0;
    int k = 0;
    std::cin >> array_length >> k;
    int *arr = new int[array_length];
    for (int i = 0; i < array_length; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKStat(arr, array_length, k);
    delete [] arr;
}