#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
    if (left == right)
        return -1;
    if (left + 1 == right)
        return a[left];
    // write your code here
    int mid = (right - left) / 2;
    int left_result = get_majority_element(a, left, mid);
    int right_result = get_majority_element(a, mid, right);
    return -1;
}

int get_majority_element_quadratic(vector<int> &a) {
    for (auto curr : a) {
        int count = 0;
        for (auto elem : a) {
            if (elem == curr)
                count++;
        }
        if (count > (int)a.size() / 2)
            return curr;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element_quadratic(a) != -11) << '\n';
    std::cout << (get_majority_element(a, 0, a.size()) != -11) << '\n';
    std::cin >> n;
}
