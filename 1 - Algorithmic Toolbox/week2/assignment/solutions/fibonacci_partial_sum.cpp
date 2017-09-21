#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <numeric>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;

    long long previous = 0;
    long long current = 1;

    for (long long i = 0; i < from - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    long long sum = current;

    for (long long i = 0; i < to - from; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

std::vector<int> get_fibonacci_period(long long m) {
    long long prev = 0;
    long long current = 1;

    std::vector<int> period{0, 1};
    do {
        long long temp_current = (current + prev) % m;
        prev = current;
        current = temp_current;
        period.push_back(current);
    } while (prev != 0 || current != 1);
    // Last two elements are the start of the following period
    period.pop_back();
    period.pop_back();
    return period;
}

int fibonacci_sum_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    std::vector<int> result = get_fibonacci_period(10);
    int nperiods10 = ((long long)n / result.size()) % 10;
    int sum = nperiods10 * std::accumulate(result.begin(), result.end(), 0);

    int r = n % result.size();
    if (r != 0)
        sum += std::accumulate(result.begin(), result.begin() + r + 1, 0);
    return sum % 10;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    if (to <= 1)
        return to;

    long long pre_last = 0;
    if (from > 0) {
        pre_last = fibonacci_sum_fast(from - 1) % 10;
    }
    long long to_last = fibonacci_sum_fast(to) % 10;

    long long sum = (to_last - pre_last) % 10;
    if (sum < 0) {
        // Normalize remainder to [0, 9]
        sum += 10;
    }
    return sum;
}

void test_solution() {
    for (int i = 0; i < 5000; ++i) {
        long long n = rand() % 30;
        int size = rand() % 5;
        std::cout << n << "\t" << size << ":\t";
        int naive = get_fibonacci_partial_sum_naive(n, n + size);
        int fast = get_fibonacci_partial_sum_fast(n, n + size);
        std::cout << naive << "\t" << fast << std::endl;
        assert(naive == fast);
    }
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    // std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    // test_solution();
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
