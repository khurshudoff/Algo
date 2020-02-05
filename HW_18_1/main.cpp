/*
Дано множество точек на плоскости (x, y).
Постройте выпуклую оболочку этого множества и вычислите ее периметр.
С помощью алгоритма Грэхема.
 */

#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>
#include <iomanip>
#include <vector>

const double EPS = 1e-15;

struct Point {
    double x = 0;
    double y = 0;
    Point(double a, double b) {
        x = a;
        y = b;
    }
};

int my_min(std::vector<Point>* arr, int n) {
    double min_y = (*arr)[0].y;
    int min_idx = 0;

    for (int i = 0; i < n; i++) {
        if ((*arr)[i].y < min_y) {
            min_y = (*arr)[i].y;
            min_idx = i;
        } else if ((*arr)[i].y == min_y){
            if ((*arr)[i].x < (*arr)[min_idx].x) {
                min_idx = i;
            }
        }
    }

    return min_idx;
}

double dist(Point p1, Point p2) {
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

double vect_multipl(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

int main() {

    int n;
    std::cin >> n;
    std::vector<Point> arr;

    // input

    for (int i = 0; i < n; i++) {
        double x = 0;
        double y = 0;
        std::cin >> x >> y;

        arr.push_back({x, y});
    }

    Point start = arr[my_min(&arr, n)];

    // sorting
    std::sort(arr.begin(), arr.end(), [&start](const Point& a, const Point& b) -> bool
    {
        double vect_mult = vect_multipl(start, a, b);
        if ((vect_mult >= -EPS) && (vect_mult <= EPS)) {
            if (dist(start, a) < dist(start, b)) {
                return true;
            } else {
                return false;
            }
        }
        return vect_mult <= 0 + EPS;
    });

    //making min convex hull

    std::stack<Point> s;
    int idx = 0;
    while (idx < n) {
        if (s.size() < 2) {
            s.push(arr[idx++]);
            continue;
        }
        Point p2 = s.top();
        s.pop();
        Point p1 = s.top();
        Point p3 = arr[idx++];

        if (vect_multipl(p1, p2, p3) < 0) {
            s.push(p2);
            s.push(p3);
        } else {
            idx--;
        }
    }


    // calculating perimetr
    Point last = s.top();
    Point first = start;

    Point cur = last;
    s.pop();

    double res = dist(last, first);

    while (!s.empty()) {
        res += dist(cur, s.top());
        cur = s.top();
        s.pop();
    }

    std::cout << std::setprecision(9) << res;

    return 0;
}
