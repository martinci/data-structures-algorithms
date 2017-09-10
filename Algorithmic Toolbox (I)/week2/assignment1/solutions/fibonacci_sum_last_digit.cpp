#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <numeric>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current = 1;
    long long sum = 1;

    for (long long i = 0; i < n - 1; ++i) {
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

void test_solution() {
    for (int i = 0; i < 5000; ++i) {
        long long n = rand() % 30;
        std::cout << n << std::endl;
        int naive = fibonacci_sum_naive(n);
        int fast = fibonacci_sum_fast(n);
        std::cout << naive << "\t" << fast << std::endl;
        assert(naive == fast);
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    // std::cout << fibonacci_sum_naive(n);
    // test_solution();
    std::cout << fibonacci_sum_fast(n) << std::endl;
}
