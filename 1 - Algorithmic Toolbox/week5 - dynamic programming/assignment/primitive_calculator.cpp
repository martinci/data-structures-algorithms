#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int min_operations(int n, vector<int> &memory, vector<int> &sequence) {
    if (n < 1) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (memory[n] != 0) {
        return memory[n];
    }
    // vector to hold the cases for n/2, n/3, n-1, if applicable, in this order
    vector<int> prev_mins(3);
    for (auto &min : prev_mins) {
        min = -1;
    }
    if (n % 2 == 0) {
        prev_mins[0] = min_operations((int)n / 2, memory, sequence);
    }
    if (n % 3 == 0) {
        prev_mins[1] = min_operations((int)n / 3, memory, sequence);
    }
    prev_mins[2] = min_operations(n - 1, memory, sequence);

    // Find minimum and index to keep track of results
    size_t min_idx = 0;
    int min = -1;
    for (size_t i = 0; i < prev_mins.size(); ++i) {
        int temp_min = prev_mins[i];
        if (temp_min != -1) {
            if (min == -1) {
                min = temp_min;
                min_idx = i;
            } else if (temp_min < min) {
                min = temp_min;
                min_idx = i;
            }
        }
    }
    // Add element to sequence
    if (min_idx == 0) {
        sequence.push_back((int)n / 2);
    } else if (min_idx == 1) {
        sequence.push_back((int)n / 3);
    } else {
        sequence.push_back(n - 1);
    }
    for (auto num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return min + 1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> memory(n + 1);
    vector<int> sequence;
    int min_ops = min_operations(n, memory, sequence);
    std::cout << min_ops << std::endl;
    for (auto num : sequence) {
        std::cout << num << " ";
    }
    std::cout << n;
    std::cin >> n;
}
