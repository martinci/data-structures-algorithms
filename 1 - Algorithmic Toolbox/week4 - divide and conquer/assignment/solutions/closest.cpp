#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::pair;
using std::min;

double distance(pair<int, int> p1, pair<int, int> p2) {
    double x2{(double)(p1.first - p2.first) * (p1.first - p2.first)};
    double y2{(double)(p1.second - p2.second) * (p1.second - p2.second)};
    return std::sqrt(x2 + y2);
}

double my_min(double a, double b) {
    if (a == -1) {
        return b;
    } else if (b == -1) {
        return a;
    } else {
        return min(a, b);
    }
}

double minimal_distance_naive(vector<pair<int, int>> &points, int lo, int hi) {
    double min{-1};
    if (lo >= hi)
        return min;
    for (int i = lo; i <= hi; ++i) {
        for (int j = i + 1; j <= hi; ++j) {
            double d = distance(points[i], points[j]);
            if (min == -1) {
                min = d;
            } else {
                if (d < min)
                    min = d;
            }
        }
    }
    return min;
}

double minimal_distance(vector<pair<int, int>> points) {
    // write your code here
    if (points.size() <= 3)
        return minimal_distance_naive(points, 0, points.size() - 1);

    std::sort(points.begin(), points.end());

    vector<pair<int, int>> left, right;
    size_t mid = (size_t)points.size() / 2; // mid is the index of the first element of right
    size_t i{0};
    while (i < mid) {
        left.push_back(points[i]);
        i++;
    }
    while (i < points.size()) {
        right.push_back(points[i]);
        i++;
    }

    double d1 = minimal_distance(left);
    double d2 = minimal_distance(right);
    double d{my_min(d1, d2)};

    // Create vector of points close to the partition boundary sorted by y-axis
    vector<pair<int, int>> boundary;
    for (auto p : points) {
        if (std::abs(p.first - points[mid].first) < d) {
            boundary.push_back(p);
        }
    }
    std::sort(boundary.begin(), boundary.end(),
              [](pair<int, int> x, pair<int, int> y) { return x.second < y.second; });

    for (size_t i = 0; i < boundary.size(); ++i) {
        double dist = minimal_distance_naive(boundary, i, min(boundary.size() - 1, i + 7));
        if (dist < d && dist != -1) {
            d = dist;
        }
    }
    return d;
    /*// vertically go through boundary using 2d-blocks that overlap on d-blocks
    size_t idx{0};
    size_t old_idx{0};
    double min_distance{d};
    while (idx < boundary.size()) {
        while (boundary[idx].second - boundary[old_idx].second < d && idx < boundary.size() - 1) {
            idx++;
        }
        size_t new_old_idx = idx;
        while (boundary[idx].second - boundary[old_idx].second < 2 * d &&
               idx < boundary.size() - 1) {
            idx++;
        }
        double temp = minimal_distance_naive(boundary, old_idx, idx);
        if (temp < min_distance && temp != -1) {
            min_distance = temp;
        }
        old_idx = new_old_idx;
    }
    return min_distance;*/
}

void test_solution() {
    while (true) {
        int n = rand() % 10 + 1;
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; ++i) {
            points[i] = std::make_pair(rand() % 11 - 5, rand() % 11 - 5);
        }
        double res = minimal_distance(points);
        double naive = minimal_distance_naive(points, 0, n - 1);
        if (res != naive) {
            std::cout << "Fail!" << std::endl;
            std::cout << n << std::endl;
            for (auto e : points) {
                std::cout << e.first << " " << e.second << std::endl;
            }

            std::cout << std::endl << "Outputs:" << std::endl;
            std::cout << "Fast: " << res << std::endl;
            std::cout << "Naive: " << naive << std::endl;
            break;
        } else {
            std::cout << "Ok!" << std::endl;
        }
    }
}

int main() {
    // test_solution();
    size_t n;
    std::cin >> n;
    vector<pair<int, int>> points(n);
    for (size_t i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        points[i] = std::make_pair(x, y);
    }
    std::cout << std::fixed;
    // std::cout << std::setprecision(9) << minimal_distance_naive(points, 0, n - 1) << "\n";
    std::cout << std::setprecision(9) << minimal_distance(points) << "\n";
    // std::cin >> n;
}
