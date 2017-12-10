#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;

vector<int> minimum_operations(int n) {
    // Since the minimum operations of n depends on the previous ones,
    // we compute min operations from 1 up to n
    vector<int> minimums(n + 1);
    minimums[1] = 0; // Redundant, included for clarity

    for (int i = 2; i <= n; ++i) {
        // Take the samallest previous min
        int min = minimums[i - 1] + 1;
        if (i % 2 == 0) {
            int temp_min = minimums[i / 2] + 1;
            if (temp_min < min) {
                min = temp_min;
            }
        }
        if (i % 3 == 0) {
            int temp_min = minimums[i / 3] + 1;
            if (temp_min < min) {
                min = temp_min;
            }
        }
        minimums[i] = min;
    }

    return minimums;
}

vector<int> recover_sequence(const int n, const vector<int> &minimums) {
    vector<int> sequence;
    int idx{n};
    do {
        sequence.push_back(idx);
        int min_idx = idx - 1;
        int min = minimums[min_idx];
        if (idx % 2 == 0) {
            int temp_min = minimums[idx / 2];
            if (temp_min < min) {
                min = temp_min;
                min_idx = idx / 2;
            }
        }
        if (idx % 3 == 0) {
            int temp_min = minimums[idx / 3];
            if (temp_min < min) {
                min = temp_min;
                min_idx = idx / 3;
            }
        }
        idx = min_idx;
    } while (idx >= 1);

    reverse(sequence.begin(), sequence.end());
    return sequence;
}

vector<int> optimal_sequence(int n) {
    std::vector<int> minimums = minimum_operations(n);
    /*for (auto num : minimums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;*/
    std::vector<int> sequence = recover_sequence(n, minimums);
    return sequence;
}

int min_operations_memoization(int n, unordered_map<int, int> &memory) {
    if (memory.count(n) == 1) {
        // std::cout << "Found one " << n << std::endl;
        return memory.at(n);
    }
    if (n == 1) {
        // The function only gets here the first time it processes 1.
        memory[1] = 0;
        return 0;
    }

    int min = min_operations_memoization(n - 1, memory) + 1;
    if (n % 2 == 0) {
        int temp_min = min_operations_memoization(n / 2, memory) + 1;
        if (min == -1 or temp_min < min) {
            min = temp_min;
        }
    }
    if (n % 3 == 0) {
        int temp_min = min_operations_memoization(n / 3, memory) + 1;
        if (min == -1 or temp_min < min) {
            min = temp_min;
        }
    }

    memory[n] = min;
    return min;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (auto num : sequence) {
        std::cout << num << " ";
    }
    // std::cin >> n;
}
