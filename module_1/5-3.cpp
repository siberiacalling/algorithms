#include <iostream>
#include <vector>
#include <algorithm>

/*
 * Смирнова Анита АПО-12
 * Contest ID 9640178
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка (Li и Righti).
 * Найти длину окрашенной части числовой прямой.
 */

struct Point {
    int value{0};
    int type{0};        // 0 - left coordinate, 1 - right coordinate
    Point(int value, int type) : value(value), type(type) {}

    Point() : value(0), type(0) {}
};

template<class T>
class IsLess {
public:
    bool operator()(const T &l, const T &r) { return l.value <= r.value; }
};

template<class T, class Compare = IsLess<T>>
void merge(T *arr, int left_index, int middle, int right_index, Compare cmp) {
    int elements_amount_left_subarray = middle - left_index + 1;
    int elements_amount_right_subarray = right_index - middle;
    T Left[elements_amount_left_subarray], Right[elements_amount_right_subarray];

    for (int i = 0; i < elements_amount_left_subarray; i++)
        Left[i] = arr[left_index + i];

    for (int j = 0; j < elements_amount_right_subarray; j++)
        Right[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left_index;
    while (i < elements_amount_left_subarray && j < elements_amount_right_subarray) {
        if (cmp(Left[i], Right[j])) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < elements_amount_left_subarray) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    while (j < elements_amount_right_subarray) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

template<class T, class Compare = IsLess<T>>
void mergeSort(T *arr, int left_index, int right_index, Compare cmp = Compare{}) {
    if (left_index < right_index) {
        int middle = left_index + (right_index - left_index) / 2;

        mergeSort(arr, left_index, middle);
        mergeSort(arr, middle + 1, right_index);

        merge(arr, left_index, middle, right_index, cmp);
    }
}

int calculateLength(Point *dots, int dots_amount) {
    int length = 0;
    int first_left = -1;
    int height = 0;

    for (int i = 0; i < dots_amount; i++) {
        if (dots[i].type == 0) {
            if (height == 0) {
                first_left = dots[i].value;
            }
            height++;
        } else {
            height--;
            if (height == 0) {
                length += dots[i].value - first_left;
            }
        }
    }
    return length;
}


int main() {
    int elements_amount = 0;
    std::cin >> elements_amount;
    int dots_amount = elements_amount * 2;
    auto *dots = new Point[dots_amount];
    int dots_index = -1;
    for (int i = 0; i < elements_amount; i++) {
        dots_index += 2;

        // l - left coordinate, r - right coordinate
        int l, r = 0;
        std::cin >> l >> r;
        dots[dots_index] = Point(l, 0);
        dots[dots_index - 1] = Point(r, 1);
    }

    mergeSort(dots, 0, dots_amount - 1);
    int result = calculateLength(dots, dots_amount);
    std::cout << result;
    delete[] dots;
    return 0;
}


