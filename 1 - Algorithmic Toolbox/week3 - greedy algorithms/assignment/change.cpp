#include <iostream>
#include <vector>
#include <cstdlib>

struct Result {
    int ncoins = 0;
    int remainder = 0;
};

Result get_change_coin(int value, int coin) {
    Result result;
    if (coin > value) {
        result.remainder = value;
    } else {
        result.ncoins = (int)value / coin;
        result.remainder = value % coin;
    }
    return result;
}

int get_change(int m) {
    int ncoins = 0;
    int value = m;
    std::vector<int> coins{10, 5, 1};
    for (int coin : coins) {
        Result coin_change = get_change_coin(value, coin);
        ncoins += coin_change.ncoins;
        value = coin_change.remainder;
    }
    return ncoins;
}

void test_solution() {
    for (int i = 0; i < 50; ++i) {
        int n = rand() % 1000 + 1;
        std::cout << "Value: " << n << "\t"
                  << "#coins: " << get_change(n) << std::endl;
    }
}

int main() {
    int m;
    std::cin >> m;
    // test_solution();
    std::cout << get_change(m) << '\n';
}
