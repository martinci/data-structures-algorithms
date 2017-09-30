#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

std::pair<int, int> partition3(vector<int> &a, vector<size_t> &tracker, int l, int r) {
    int x = a[l]; // x is the pivot
    int j = -1;   // tracks "less" block
    int k = l;    // tracks "equal" block
    for (int i = l + 1; i <= r; i++) {
        if (a[i] == x) { // swap with the element right above the equal block
            k++;
            std::swap(a[i], a[k]);
            std::swap(tracker[i], tracker[k]);
        } else if (a[i] < x) { // swap below equal block, then fix equal block
            if (j != -1) {
                j++;
            } else {
                j = l;
            }
            std::swap(a[i], a[j]);
            std::swap(tracker[i], tracker[j]);
            k++;
            std::swap(a[i], a[k]);
            std::swap(tracker[i], tracker[k]);
        }
    }
    std::pair<int, int> p;
    p.first = j;
    p.second = k;
    return p;
}

void quick3_sort_index(vector<int> &a, vector<size_t> &tracker, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    std::swap(a[l], a[k]);
    std::swap(tracker[l], tracker[k]);
    auto p = partition3(a, tracker, l, r);

    quick3_sort_index(a, tracker, l, p.first);
    quick3_sort_index(a, tracker, p.second + 1, r);
}

int binary_search(int x, vector<int> &vec, int lo, int hi) {
    if (lo > hi) {
        // In our application below this case can't happen
        return -1;
    }
    int mid = lo + (hi - lo) / 2;
    if (vec[mid] == x) {
        return mid;
    } else if (x < vec[mid]) {
        return binary_search(x, vec, lo, mid - 1);

    } else {
        return binary_search(x, vec, mid + 1, hi);
    }
}

vector<std::pair<int, int>> get_line_of_pairs(vector<int> &starts, vector<int> &ends) {
    vector<std::pair<int, int>> line(starts.size() + ends.size());
    // Fill vector with all elements in the problem
    for (size_t i = 0; i < starts.size(); ++i) {
        line[2 * i] = std::make_pair(starts[i], 0);
        line[2 * i + 1] = std::make_pair(ends[i], 2);
    }
    std::sort(line.begin(), line.end());
    return line;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> counts(points.size());
    // line is sorted
    auto line = get_line_of_pairs(starts, ends);
    // sort points while tracking index
    vector<size_t> tracker(points.size());
    for (size_t i = 0; i < tracker.size(); ++i) {
        tracker[i] = i;
    }
    quick3_sort_index(points, tracker, 0, points.size() - 1);

    int count{0};
    size_t i{0};
    size_t j{0};
    while (i < line.size() && j < points.size()) {
        if (line[i] < std::make_pair(points[j], 1)) {
            if (line[i].second == 0) {
                count++;
            } else {
                count--;
            }
            i++;
        } else {
            counts[tracker[j]] = count;
            j++;
        }
    }
    // fill any left over points count
    for (; j < points.size(); ++j) {
        counts[tracker[j]] = count;
    }

    return counts;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

void test_solution() {
    while (true) {
        int n = rand() % 5 + 1;
        vector<int> starts(n), ends(n);
        for (size_t i = 0; i < starts.size(); ++i) {
            starts[i] = rand() % 10 + 1;
            ends[i] = starts[i] + rand() % 10 + 1;
        }
        int m = rand() % 4 + 1;
        vector<int> points(m);
        for (size_t i = 0; i < points.size(); ++i) {
            points[i] = rand() % 20 + 1;
        }
        vector<int> res = fast_count_segments(starts, ends, points);
        vector<int> naive = naive_count_segments(starts, ends, points);
        if (res != naive) {
            std::cout << "Fail!" << std::endl;
            std::cout << starts.size() << " " << points.size() << std::endl;
            for (size_t i = 0; i < starts.size(); ++i) {
                std::cout << starts[i] << " " << ends[i] << std::endl;
            }
            for (size_t i = 0; i < points.size(); ++i) {
                std::cout << points[i] << " ";
            }
            std::cout << std::endl << "Outputs:" << std::endl << "Fast: ";
            for (auto e : res) {
                std::cout << e << " ";
            }
            std::cout << std::endl << "Naive: ";
            for (auto e : naive) {
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
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    /*vector<int> cnt_naive = naive_count_segments(starts, ends, points);
    for (auto e : cnt_naive) {
        std::cout << e << ' ';
    }*/
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
    // std::cin >> n;
}
