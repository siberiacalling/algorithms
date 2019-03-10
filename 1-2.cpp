#include <iostream>
#include <vector>
#include <tgmath.h>

/*
 * Смирнова Анита АПО-12
 * Contest ID 19564272
 * Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
 * Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин
 * в порядке обхода против часовой стрелки.
 * n < 1000, координаты < 10000.
 */

struct Point {
    int x{0};
    int y{0};
    Point(int x, int y) : x(x), y(y) {}
};

double calulate_area(std::vector<Point> dots) {
    double area = 0;
    for (int i = 0; i < dots.size(); i++) {
        if (i == dots.size() - 1) {
            area += (dots[i].x + dots[0].x) * (dots[0].y - dots[i].y);
        } else {
            area += (dots[i].x + dots[i + 1].x) * (dots[i + 1].y - dots[i].y);
        }
    }
    return fabs(area / 2);
}

int main() {
    int coordinates_amount;
    std::vector<Point> dots;
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