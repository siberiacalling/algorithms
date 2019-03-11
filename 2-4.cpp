#include <iostream>
#include <vector>
#include <limits>

/*
 * Смирнова Анита АПО-12
 * Contest ID
 *  Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 *  Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 *  ближайшего по значению к B[i]. Время работы поиска для каждого элемента B[i]: O(log(k)).
 *  n ≤ 110000, m ≤ 1000.
 */
std::vector<int> read_array() {
    std::vector<int> my_array;
    int elements_amount;
    std::cin >> elements_amount;
    for (int i = 0; i < elements_amount; i++) {
        int tmp;
        std::cin >> tmp;
        my_array.push_back(tmp);
    }
    return my_array;
}

//int get_borders(int target, const std::vector<int> &A) {
//    int max_power = 1;
//    while (A[max_power] < target) {
//        max_power *=2;
//    }
//    return max_power;
//}
int binary_search_index(int target, const std::vector<int> &A) {
    int vector_size = static_cast<int>(A.size()) - 1;
    int left = 0;
    int right = vector_size;

    int index = -1;
    int distance = std::numeric_limits<int>::max();
    while (left <= right) {
        int middle = left + (-left + right) / 2;
        if (abs(target - A[middle]) < distance) {
            distance = abs(target - A[middle]);
            index = middle;
        } else if (abs(target - A[middle]) == distance) {
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

std::vector<int> find_indexes(const std::vector<int> &A, const std::vector<int> &B) {
    std::vector<int> indexes;
    for (int b : B) {
        int current_index = binary_search_index(b, A);
        indexes.push_back(current_index);
    }
    return indexes;
}

int main() {
    std::vector<int> A = read_array();
    std::vector<int> B = read_array();
    std::vector<int> result = find_indexes(A, B);
    for (int r : result) {
        std::cout << r << " ";
    }

    return 0;
}