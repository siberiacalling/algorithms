#include <iostream>
#include <vector>
#include <tgmath.h>

struct Pair {
    int x{0};
    int y{0};

    Pair(int x, int y) : x(x), y(y) {}
};

double calulate_area(std::vector<Pair> dots) {
    double area = 0;
    for (int i = 0; i < dots.size(); i++) {
        if (i == dots.size() - 1) {
            area += (dots[i].x + dots[0].x) * (dots[0].y - dots[i].y);
        }
        else {
            area += (dots[i].x + dots[i + 1].x) * (dots[i + 1].y - dots[i].y);
        }
    }
    return fabs(area/2);
}

int main() {
    int coordinates_amount;
    std::vector<Pair> dots;
    std::cin >> coordinates_amount;
    for (int i = 0; i < coordinates_amount; i++) {
        int x, y;
        std::cin >> x >> y;
        dots.emplace_back(x, y);
    }
    double area = calulate_area(dots);
    std::cout << area;
    return 0;
}