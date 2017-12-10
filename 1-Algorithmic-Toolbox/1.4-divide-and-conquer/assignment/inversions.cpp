#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

long long count_inversions_naive(vector<int> &a) {
    long long count = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = i + 1; j < (int)a.size(); ++j) {
            if (a[i] > a[j])
                count++;
        }
    }
    return count;
}

long long merge_and_count(vector<int> &b, size_t left, size_t mid, size_t right) {
    long long count{0};
    vector<int> temp(right - left + 1);
    size_t left_idx = left;
    size_t right_idx = mid + 1;
    size_t i = 0;
    while (left_idx <= mid && right_idx <= right) {
        if (b[left_idx] <= b[right_idx]) {
            temp[i] = b[left_idx];
            left_idx++;
        } else {
            temp[i] = b[right_idx];
            right_idx++;
            count += mid - left_idx + 1;
        }
        i++;
    }
    // Fill the rest of temp
    if (left_idx > mid) {
        while (right_idx <= right) {
            temp[i] = b[right_idx];
            right_idx++;
            i++;
        }
    } else {
        while (left_idx <= mid) {
            temp[i] = b[left_idx];
            left_idx++;
            i++;
        }
    }
    // Reflect changes in b
    for (size_t i = 0; i < temp.size(); ++i) {
        b[left + i] = temp[i];
    }
    return count;
}

long long count_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long count = 0;
    if (right <= left)
        return count;
    size_t mid = (size_t)(left + right) / 2;
    count += count_inversions(a, b, left, mid);
    count += count_inversions(a, b, mid + 1, right);
    // merge sorted array b and add counts
    count += merge_and_count(b, left, mid, right);
    return count;
}

void test_solution() {
    while (true) {
        int n = rand() % 10 + 1;
        vector<int> a(n);
        for (size_t i = 0; i < a.size(); ++i) {
            a[i] = rand() % 10 + 1;
        }
        vector<int> b(a);
        int res = count_inversions(a, b, 0, a.size() - 1);
        int naive = count_inversions_naive(a);
        if (res != naive) {
            std::cout << "Fail!"
                      << "\t" << res << " " << naive << std::endl;
            std::cout << n << std::endl;
            for (auto e : a) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
            for (auto e : b) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
            break;
        } else {
            std::cout << "Ok!" << std::endl;
        }
    }
}

int main() {
    // test_solution();
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a);
    std::cout << count_inversions(a, b, 0, a.size() - 1) << std::endl;
    // std::cout << count_inversions_naive(a) << std::endl;
    // std::cin >> n;
}
