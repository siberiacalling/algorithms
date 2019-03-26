#include <iostream>
#include <fstream>

/*
 * Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.*/

// return byte №. byte_num
long long digit(long long val, int byte_num) {
    for (int i = 0; i < byte_num; i++) {
        val = val >> 8;
    }
    return val & 255;
}

// LSD
long long*  radixSort(long long *arr, int array_length) {
    int *digits_count = new int[256];
    auto result = new long long[array_length]();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 256; j++) {
            digits_count[j] = 0;
        }
        for (int j = 0; j < array_length; j++) {
            long long current_digit = digit(arr[j], i);
            digits_count[current_digit]++;
        }
        int count = 0;
        for (int j = 0; j < 256; j++) {
            long long tmp = digits_count[j];
            digits_count[j] = count;
            count += tmp;
        }
        int last_index = array_length - 1;
        for (int j = 0; j < last_index + 1; j++) {
            long long current_digit = digit(arr[j], i);
            result[digits_count[current_digit]] = arr[j];
            digits_count[current_digit] += 1;
        }
        for (int i = 0; i < array_length; i ++){
            arr[i] = result[i];

        }
    }
    delete [] digits_count;
    return result;
}

int main() {
    int array_length = 0;
    int k = 0;
    std::cin >> array_length;
    auto *arr = new long long[array_length];
    for (int i = 0; i < array_length; i++) {
        std::cin >> arr[i];
    }

    long long * result = radixSort(arr, array_length);
    for (int i = 0; i < array_length; i++) {
        std::cout << result[i] << " ";
    }
    delete[]arr;
    delete[]result;

}