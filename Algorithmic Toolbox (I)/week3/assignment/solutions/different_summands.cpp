#include <iostream>
#include <vector>

using std::vector;

int gauss_sum(int n) { return (int)(n * (n + 1) / 2); }

vector<int> optimal_summands(int n) {
    // The number of children must be the biggest triangular number that fits in n.
    int k = 1;
    vector<int> summands;
    while (gauss_sum(k) <= n) {
        summands.push_back(k);
        k++;
    }
    // k-1 is the las triangular number <= n.
    // Add leftover candy to the winner
    summands[k - 2] += n - gauss_sum(k - 1);
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
    // std::cin >> n;
}
