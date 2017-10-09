#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;

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

std::pair<long long, long long> min_and_max(int i, int j, const vector<long long> &digits,
                                            const vector<char> &operations) {
    long long min_value = std::numeric_limits<long long>::max();
    long long max_value = std::numeric_limits<long long>::min();

    for (int k = i; k < j; ++k) {
        auto pair_left = min_and_max(i, k, digits, operations);
        auto pair_right = min_and_max(k + 1, j, digits, operations);
        long long a = eval(pair_left.second, pair_right.second, operations[k]);
        long long b = eval(pair_left.second, pair_right.first, operations[k]);
        long long c = eval(pair_left.first, pair_right.second, operations[k]);
        long long d = eval(pair_left.first, pair_right.first, operations[k]);
        min_value = std::min(min_value, a, b, c, d);
        max_value = std::max(max_value, a, b, c, d);
    }

    return {min_value, max_value};
}

long long get_maximum_value(const string &expr) {
    vector<long long> digits;
    vector<char> operations;
    int n = expr.size();
    for (size_t i = 0; i < n - 1; i += 2) {
        digits.push_back(expr[i]);
        operations.push_back(expr[i + 1]);
    }
    digits.push_back(expr[n - 1]);
    long long max_value = min_and_max(0, digits.size() - 1, digits, operations).second;
    return max_value;
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
    std::cin >> s;
}
