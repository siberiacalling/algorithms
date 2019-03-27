#include <iostream>
#include <fstream>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19792893
 * Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
 * Отсортировать массив методом поразрядной сортировки LSD по байтам.
 */

std::uint64_t digit(std::uint64_t val, int byte_num) {
    for (int i = 0; i < byte_num; i++) {
        val = val >> 8;
    }
    return val & 255;
}

std::uint64_t *radixLsdSort(std::uint64_t *arr, int array_length) {
    int *digits_count = new int[256];
    auto result = new std::uint64_t[array_length]();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 256; j++) {
            digits_count[j] = 0;
        }
        for (int j = 0; j < array_length; j++) {
            std::uint64_t current_digit = digit(arr[j], i);
            digits_count[current_digit]++;
        }
        int count = 0;
        for (int j = 0; j < 256; j++) {
            auto tmp = static_cast<uint64_t>(digits_count[j]);
            digits_count[j] = count;
            count += tmp;
        }
        int last_index = array_length - 1;
        for (int j = 0; j < last_index + 1; j++) {
            std::uint64_t current_digit = digit(arr[j], i);
            result[digits_count[current_digit]] = arr[j];
            digits_count[current_digit] += 1;
        }
        for (int j = 0; j < array_length; j++) {
            arr[j] = result[j];
        }
    }
    delete[] digits_count;
    return result;
}

int main() {
    int array_length = 0;
    std::cin >> array_length;
    auto *arr = new std::uint64_t[array_length];
    for (int i = 0; i < array_length; i++) {
        std::cin >> arr[i];
    }

    std::uint64_t *result = radixLsdSort(arr, array_length);
    for (int i = 0; i < array_length; i++) {
        std::cout << result[i] << " ";
    }
    delete[]arr;
    delete[]result;

}