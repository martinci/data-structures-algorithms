#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::vector;

struct OptimalIdx {
    int idx{-1};
    double ratio{-1};
};

OptimalIdx get_optimal_index(vector<int> &weights, vector<int> &values) {
    OptimalIdx optimal;
    for (size_t i = 0; i < weights.size(); ++i) {
        double ratio{(double)values[i] / weights[i]};
        if (ratio > optimal.ratio) {
            optimal.ratio = ratio;
            optimal.idx = i;
        }
    }
    return optimal;
}

double get_optimal_value(int capacity, vector<int> &weights, vector<int> &values) {
    double value = 0.0;
    int current_capacity{capacity};
    while (current_capacity > 0 && not weights.empty()) {
        OptimalIdx optimal = get_optimal_index(weights, values);
        int a = std::min(current_capacity, weights[optimal.idx]);
        value += (double)a * optimal.ratio;
        current_capacity -= a;
        weights.erase(weights.begin() + optimal.idx);
        values.erase(values.begin() + optimal.idx);
    }
    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    // std::cin >> n;
    return 0;
}
