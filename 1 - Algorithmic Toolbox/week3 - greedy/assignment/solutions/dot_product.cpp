#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;

int find_max_idx(vector<int> v) {
    int idx{-1};
    if (v.empty())
        return idx;
    idx = 0;
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] > v[idx])
            idx = i;
    }
    return idx;
}

long long max_dot_product(vector<int> &a, vector<int> &b) {
    long long result = 0;
    while (not a.empty()) {
        int a_idx = find_max_idx(a);
        int b_idx = find_max_idx(b);
        result += (long long)a[a_idx] * b[b_idx];
        a.erase(a.begin() + a_idx);
        b.erase(b.begin() + b_idx);
    }
    return result;
}

vector<int> get_rand_vec(size_t n) {
    vector<int> vec(n);
    for (size_t idx = 0; idx < n; ++idx) {
        vec[idx] = rand() % 100 - 50;
    }
    return vec;
}

void test_solution() {
    for (int i = 0; i < 100; ++i) {
        int n = rand() % 5 + 1;
        vector<int> a = get_rand_vec((size_t)n);
        vector<int> b = get_rand_vec((size_t)n);
        for (auto element : a)
            std::cout << element << " ";
        std::cout << std::endl;
        for (auto element : b)
            std::cout << element << " ";
        std::cout << std::endl;
        std::cout << "result: " << max_dot_product(a, b) << std::endl;
    }
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::cout << max_dot_product(a, b) << std::endl;
    // test_solution();
    std::cin >> n;
}
