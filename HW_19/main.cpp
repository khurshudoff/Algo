#include <iostream>
#include <vector>

const int two_10 = 1024;
const int max_depth = 10;

struct Point {
    double x=0;
    double y=0;
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

std::vector<bool> int2bin(int v) {
    int i = 9;
    std::vector<bool> res(10);
    while (v > 0) {
        res[i--] = v % 2;
        v /= 2;
    }
    return res;
}

std::pair< std::pair<double, double>, std::pair<double, double> > way2coords (std::vector<bool> way) {
    double left = -180;
    double right = 180;
    double down = -180;
    double top = 180;

    for (int i = 0; i < way.size(); i++) {
        if (i % 2 == 0) {
            //split x
            if (way[i] == 0) {
                left = (right + left) / 2;
            } else {
                right = (right + left) / 2;
            }
        } else {
            if (way[i] == 0) {
                down = (down + top) / 2;
            } else {
                top = (down + top) / 2;
            }
        }
    }
    return std::make_pair(std::make_pair(left, down), std::make_pair(right, top));
}

struct TreeNode {
    explicit TreeNode(int _value) : value(_value) {}

    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    std::vector<int> idxs_of_points;
};

class Tree {
public:
    Tree (std::vector<Point> _points);
    int find_in_rect(double x1, double y1, double x2, double y2);
private:
    std::vector<Point> points;
    TreeNode* root = nullptr;
    int find_in_rect_help(double x1, double y1, double x2, double y2, bool dir, TreeNode* cur, std::vector<bool> way);
};

Tree::Tree (std::vector<Point> _points) {
    points = _points;
    int n = points.size();
    root = new TreeNode(n);

    for (int i = 0; i < n; i++) {

        std::vector<bool> bin_x = int2bin((int) ((points[i].x + 180) / 360 * two_10) );
        std::vector<bool> bin_y = int2bin((int) ((points[i].y + 180) / 360 * two_10) );

        std::vector<bool> bin_all;
        for (int i = 0; i < 10; i++) {
            bin_all.push_back(bin_x[i]);
            bin_all.push_back(bin_y[i]);
        }

        TreeNode** cur = &root;

        for (int j = 0; j < bin_all.size(); j++) {
            if (bin_all[j] == 0) {
                if ((*cur)->left == nullptr) {
                    (*cur)->left = new TreeNode(1);
                } else {
                    (*cur)->left->value += 1;
                }
                (*cur)->idxs_of_points.push_back(i);
                cur = &((*cur)->left);
            } else {
                if ((*cur)->right == nullptr) {
                    (*cur)->right = new TreeNode(1);
                } else {
                    (*cur)->right->value += 1;
                }
                (*cur)->idxs_of_points.push_back(i);
                cur = &((*cur)->right);
            }
        }
    }
}
int Tree::find_in_rect(double x1, double y1, double x2, double y2) {
    double l = -180;
    double d = -180;
    double r = 180;
    double t = 180;
    return find_in_rect_help(x1, y1, x2, y2, 0, root, std::vector<bool>());
}

int Tree::find_in_rect_help(double x1, double y1, double x2, double y2, bool dir, TreeNode* cur, std::vector<bool> way) {
    if (cur == nullptr) return 0;

    auto [tmp1, tmp2] = way2coords(way);
    auto [left, down] = tmp1;
    auto [right, top] = tmp2;
    x1 = std::max(left, x1);
    y1 = std::max(down, y1);
    x2 = std::min(right, x2);
    y2 = std::min(top, y2);

    if ((x1 >= right) || (x2 < left) || (y1 >= top) || (y2 < down)) return 0;
    if ((left >= x1) && (right < x2) && (down >= y1) && (top < y2)) return cur->value;

    if (way.size() == max_depth) {
        // check points
        int cnt = 0;
        for (auto idx : cur->idxs_of_points) {
            auto [cur_x, cur_y] = points[idx];
            if ((cur_x >= x1) && (cur_x < x2) && (cur_y >= y1) && (cur_y < y2)) {
                cnt += 1;
            }
        }
        return cnt;
    }

    std::vector<bool> left_way = way;
    std::vector<bool> right_way = way;
    left_way.push_back(1);
    right_way.push_back(0);

    return find_in_rect_help(x1, y1, x2, y2, !dir, (*cur).left, left_way) +
           find_in_rect_help(x1, y1, x2, y2, !dir, (*cur).right, right_way);
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<Point> points;
    for (int i = 0; i < n; i++) {
        double x = 0;
        double y = 0;
        std::cin >> x >> y;
        points.push_back(Point(x, y));
    }

    Tree tree(points);

    int m = 0;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        double x1 = 0;
        double x2 = 0;
        double y1 = 0;
        double y2 = 0;

        std::cin >> x1 >> y1 >> x2 >> y2;

        std::cout << tree.find_in_rect(x1, y1, x2, y2) << std::endl;
    }
    return 0;
}