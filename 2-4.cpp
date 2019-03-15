#include <iostream>
#include <vector>
#include <limits>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19640154
 * Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 * ближайшего по значению к B[i]. Время работы поиска для каждого элемента B[i]: O(log(k)).
 * n ≤ 110000, m ≤ 1000.
 */

std::vector<int> read_array() {
    unsigned long elements_amount = 0;
    std::cin >> elements_amount;
    std::vector<int> my_array(elements_amount);
    for (int i = 0; i < elements_amount; i++) {
        int tmp = 0;
        std::cin >> tmp;
        my_array[i] = tmp;
    }
    return my_array;
}

std::pair<int, int> get_borders(int target, const std::vector<int> &A) {        // O(log(n)) time, O(1) memory
    int max_index = static_cast<int>(A.size()) - 1;
    int left = 0;
    int right = max_index;
    int max_power = 1;
    while ((A[max_power] < target) && (max_power < max_index)) {
        max_power *= 2;
    }
    if (max_power <= max_index) {
        right = max_power;
    }
    left = max_power / 2;
    return {left, right};
}

int binary_search_index(int target, const std::vector<int> &A) {                // O(log(n)) time, O(1) memory
    auto left_right = get_borders(target, A);
    int left = left_right.first;
    int right = left_right.second;
    int index = -1;
    int distance = std::numeric_limits<int>::max();
    while (left <= right) {
        int middle = left + (-left + right) / 2;
        int current_distance = std::abs(target - A[middle]);
        if (current_distance < distance) {
            distance = abs(target - A[middle]);
            index = middle;
        } else if (current_distance == distance) {
            index = std::min(middle, index);
        }
        if (target < A[middle]) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    if (index == -1) {
        index = 0;
    }
    return index;
}

std::vector<int> find_indexes(const std::vector<int> &A, const std::vector<int> &B) {       // O(nlog(n)) time, O(n) memory
    std::vector<int> indexes(B.size());
    for (int i = 0; i < B.size(); i++) {
        int current_index = binary_search_index(B[i], A);
        indexes[i] = current_index;
    }
    return indexes;
}

int main() {
    const std::vector<int> A = read_array();
    const std::vector<int> B = read_array();
    const std::vector<int> result = find_indexes(A, B);
    for (const auto r : result) {
        std::cout << r << " ";
    }

    return 0;
}