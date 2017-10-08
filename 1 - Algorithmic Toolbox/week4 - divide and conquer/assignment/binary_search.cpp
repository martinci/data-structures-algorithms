#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x, int lo, int hi) {
    // write your code here
    if (lo > hi) {
        return -1;
    }
    int mid = (int)(hi + lo) / 2;

    if (x < a[mid]) {
        return binary_search(a, x, lo, mid - 1);
    } else if (a[mid] < x) {
        return binary_search(a, x, mid + 1, hi);
    } else {
        return mid;
    }
}

int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x)
            return i;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        // replace with the call to binary_search when implemented
        // std::cout << linear_search(a, b[i]) << ' ';
        std::cout << binary_search(a, b[i], 0, n - 1) << ' ';
    }
    // std::cin >> n;
}
