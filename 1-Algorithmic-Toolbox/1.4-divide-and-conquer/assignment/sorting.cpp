#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

int partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    std::swap(a[l], a[k]);
    int m = partition2(a, l, r);

    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, m + 1, r);
}

struct Pair {
    int less_idx;
    int eq_idx;
};

Pair partition3(vector<int> &a, int l, int r) {
    int x = a[l]; // x is the pivot
    int j = -1;   // tracks "less" block
    int k = l;    // tracks "equal" block
    for (int i = l + 1; i <= r; i++) {
        if (a[i] == x) { // swap with the element right above the equal block
            k++;
            std::swap(a[i], a[k]);
        } else if (a[i] < x) { // swap below equal block, then fix equal block
            if (j != -1) {
                j++;
            } else {
                j = l;
            }
            std::swap(a[i], a[j]);
            k++;
            std::swap(a[i], a[k]);
        }
    }
    Pair p;
    p.less_idx = j;
    p.eq_idx = k;
    return p;
}

void randomized_quick3_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    std::swap(a[l], a[k]);
    Pair p = partition3(a, l, r);

    randomized_quick3_sort(a, l, p.less_idx);
    randomized_quick3_sort(a, p.eq_idx + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    // randomized_quick_sort(a, 0, a.size() - 1);
    randomized_quick3_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cin >> n;
}
