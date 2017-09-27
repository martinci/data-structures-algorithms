#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

int get_count(vector<int> &vec, int x, int lo, int hi) {
    int count{0};
    for (int i = lo; i <= hi; ++i) {
        if (vec[i] == x)
            count++;
    }
    return count;
}

int get_majority_element(vector<int> &a, int left, int right) {
    if ((left + 1 == right && a[left] == a[right]) || left == right)
        return a[left];
    if (left + 1 == right && a[left] != a[right])
        return -1;

    // write your code here
    int mid = (int)(right + left) / 2;
    // std::cout << "mid = " << mid << "\t" << a[mid] << std::endl;
    int left_result = get_majority_element(a, left, mid);
    int right_result = get_majority_element(a, mid + 1, right);

    // std::cout << left_result << "\t" << right_result << std::endl;

    if (left_result == right_result) {
        return left_result;
    } else {
        if (left_result != -1) {
            int count = get_count(a, left_result, left, right);
            if (count > (int)(right - left + 1) / 2)
                return left_result;
        }
        if (right_result != -1) {
            int count = get_count(a, right_result, left, right);
            if (count > (int)(right - left + 1) / 2)
                return right_result;
        }
    }
    return -1;
}

int get_majority_element_quadratic(vector<int> &a) {
    for (auto curr : a) {
        int count = get_count(a, curr, 0, (int)a.size() - 1);
        if (count > (int)a.size() / 2)
            return curr;
    }
    return -1;
}

void test_solution() {
    while (true) {
        int n = rand() % 100 + 1;
        vector<int> a(n);
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = rand() % 10 + 1;
        }
        int res = get_majority_element(a, 0, n - 1);
        int naive = get_majority_element_quadratic(a);
        if (res != naive) {
            std::cout << "Fail!" << std::endl;
            std::cout << n << std::endl;
            for (auto e : a) {
                std::cout << e << " ";
            }
        } else {
            std::cout << "Ok!" << std::endl;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    // std::cout << (get_majority_element_quadratic(a) != -1) << '\n';
    // test_solution();
    std::cout << (get_majority_element(a, 0, a.size() - 1) != -1) << '\n';
    // std::cin >> n;
}
