#include <iostream>
#include <cassert>
#include <cstdlib>

long long get_fibonacci_huge_naive(long long n, long long m) {
  if (n <= 1)
    return n;

  long long previous = 0;
  long long current = 1;

  for (long long i = 0; i < n - 1; ++i) {
    long long tmp_previous = previous;
    previous = current;
    current = (tmp_previous + current) % m;
  }

  return current;
}

long long fibonacci_fast(long long n, long long m) {
  // write your code here
  if (n <= 1) {
    return n;
  }

  long long prev = 0;
  long long current = 1;

  for (long long i = 2; i <= n; ++i) {
    long long temp_current = (current + prev) % m;
    prev = current;
    current = temp_current;
  }

  return current;
}

long long get_fibonacci_period_lenght(long long m) {
  long long prev = 0;
  long long current = 1;

  long long period = 0;
  // long long temp_current = 0;
  do {
    long long temp_current = (current + prev) % m;
    prev = current;
    current = temp_current;
    period++;
  } while (prev != 0 || current != 1);

  return period;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
  long long period = get_fibonacci_period_lenght(m);
  long long r = n % period;
  return fibonacci_fast(r, m);
}

void test_solution() {
  for (long long i = 1; i < 20; ++i) {
    long a = rand() % 20;
    long long b = rand() % 8 + 2;
    assert(get_fibonacci_huge_fast(a, b) == get_fibonacci_huge_naive(a, b));
  }
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
  // test_solution();
  // std::cout << get_fibonacci_period(n) << '\n';
  std::cout << get_fibonacci_huge_fast(n, m) << '\n';
  return 0;
}
