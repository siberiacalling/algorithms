/*
 * Найти k-ю порядковую статистику
 * Реализация с семинара
 */

#include <algorithm>
#include <iostream>

int partition(int *arr, int n) {
    int pivot = arr[n - 1];
    int i = 0;
    int j = n - 2;
    while (true) {
        while (i <= n - 1 && arr[i] < pivot) {
            i++;
        }
        while (j >= 0 && arr[i] > pivot) {
            j--;
        }
        if (i >= j) {
            std::swap(arr[n - 1], arr[i]);
            return i;
        }
        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }

}

int findKStat(int *arr, int n, int k) {
    int pivotPos = partition(arr, n);
    if (k == pivotPos) {
        return arr[k];
    }
    if (k < pivotPos) {
        return findKStat(arr, pivotPos, k);
    }
    return findKStat(arr, n - pivotPos - 1, k - pivotPos);
}

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKStat(arr, n, k);
}