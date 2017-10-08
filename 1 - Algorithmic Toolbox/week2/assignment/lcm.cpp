#include <iostream>
#include <cassert>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long)a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long)a * b;
}

int gcd_fast(int a, int b) {
  if (b == 0) {
    return a;
  }

  int result{0};
  if (a > b) {
    result = gcd_fast(b, a % b);
  } else {
    result = gcd_fast(a, b % a);
  }

  return result;
}

long long lcm_fast(int a, int b) {
  // a*b = lcm(a,b) * gcd(a,b)
  return (long long)a * b / gcd_fast(a, b);
}

void test_solution() {
  for (int a = 1; a < 20; ++a) {
    for (int b = 1; b < 20; ++b) {
      assert(lcm_fast(a, b) == lcm_naive(a, b));
    }
  }
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // test_solution();
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
