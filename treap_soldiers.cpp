#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int v1, int v2) : x(v1), y(v2) {}
    Point() = default;
};

double CalculateTriangleArea(const Point& p1, const Point& p2, const Point& p3) {
    double side12 = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    double side13 = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
    double side23 = sqrt(pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2));

    double semiPerimeter = (side12 + side13 + side23) / 2;
    double area = sqrt(semiPerimeter * (semiPerimeter - side12) * (semiPerimeter - side13) * (semiPerimeter - side23));
    return area;
}

double CalculatePolygonArea(size_t n, const vector<Point>& vertices) {
    double area = 0;
    const Point& origin = vertices[0];
    for (size_t i = 1; i < n - 1; ++i) {
        area += CalculateTriangleArea(origin, vertices[i], vertices[i + 1]);
    }
    return area;
}

int main() {
    size_t n;
    cin >> n;
    vector<Point> vertices(n);

    for (size_t i = 0; i < n; ++i) {
        cin >> vertices[i].x >> vertices[i].y;
    }

    cout << CalculatePolygonArea(n, vertices) << endl;

    return 0;
}

//3
// 1 0
// 0 1
// 0 1