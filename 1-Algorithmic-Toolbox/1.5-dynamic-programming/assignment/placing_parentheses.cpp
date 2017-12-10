#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <utility>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;

// Helper function to output a matrix in the console.
template <class T> void display(vector<vector<T>> &matrix) {
    for (auto &row : matrix) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

std::pair<long long, long long> min_and_max(int i, int j, const vector<char> &operations,
                                            const vector<vector<long long>> &mins,
                                            vector<vector<long long>> &maxes) {
    long long min_value = std::numeric_limits<long long>::max();
    long long max_value = std::numeric_limits<long long>::min();

    for (int k = i; k < j; ++k) {
        auto left_min = mins[i][k];
        auto left_max = maxes[i][k];
        auto right_min = mins[k + 1][j];
        auto right_max = maxes[k + 1][j];

        long long a = eval(left_max, right_max, operations[k]);
        long long b = eval(left_max, right_min, operations[k]);
        long long c = eval(left_min, right_max, operations[k]);
        long long d = eval(left_min, right_min, operations[k]);

        vector<long long> min_vec{min_value, a, b, c, d};
        vector<long long> max_vec{max_value, a, b, c, d};
        min_value = *std::min_element(min_vec.begin(), min_vec.end());
        max_value = *std::max_element(max_vec.begin(), max_vec.end());
    }
    return {min_value, max_value};
}

long long get_maximum_value(const string &expr) {
    // Separate digits and operations for convenience
    std::set<char> ops{'+', '-', '*'};
    vector<char> operations;
    for (auto c : expr) {
        if (ops.count(c))
            operations.push_back(c);
    }
    vector<long long> digits;
    size_t i = 0;
    size_t j = 0;
    string digit;
    while (i < operations.size()) {
        char c = expr[j];
        if (ops.count(c)) {
            digits.push_back(std::stoll(digit));
            digit = "";
            ++i;
        } else {
            digit += c;
        }
        ++j;
    }
    // Add the last digit
    while (j < expr.size()) {
        digit += expr[j];
        ++j;
    }
    digits.push_back(std::stoll(digit));

    // Set up matrices for dynamic programming
    size_t n = digits.size();
    vector<vector<long long>> mins(n);
    vector<vector<long long>> maxes(n);
    for (auto &min_row : mins) {
        min_row.resize(n);
    }
    for (auto &max_row : maxes) {
        max_row.resize(n);
    }

    // Initialize mins and maxes
    for (size_t i = 0; i < n; ++i) {
        mins[i][i] = digits[i];
        maxes[i][i] = digits[i];
    }

    for (size_t s = 1; s < n; ++s) {
        for (size_t i = 0; i < n - s; ++i) {
            size_t j = i + s;
            auto min_max_pair = min_and_max(i, j, operations, mins, maxes);
            mins[i][j] = min_max_pair.first;
            maxes[i][j] = min_max_pair.second;
        }
    }
    // display(mins);
    // display(maxes);
    return maxes[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
    // std::cin >> s;
}
