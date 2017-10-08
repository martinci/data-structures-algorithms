#include <iostream>
#include <vector>

using std::vector;

// Greedy algorithm, suboptimal solution
int greedy_weight(int W, const vector<int> &weights) {
    int current_weight = 0;
    for (size_t i = 0; i < weights.size(); ++i) {
        if (current_weight + weights[i] <= W) {
            current_weight += weights[i];
        }
    }
    return current_weight;
}

// Helper function to output a matrix in the console.
void display(vector<vector<int>> &matrix) {
    for (auto &row : matrix) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int optimal_weight(int W, const vector<int> &weights) {
    // Dynamic programming approach, set up a (n+1)x(W+1) matrix of results.
    // Note that it is initialized to 0s by default, which works for us.
    int n = weights.size();
    vector<vector<int>> optimal_results(n + 1);
    for (auto &row : optimal_results) {
        row.resize(W + 1);
    }

    for (int K = 1; K <= W; ++K) {
        for (int i = 1; i <= n; ++i) {
            // Compute solution for total weight K only using up to the i-th weight.
            int max_weight = optimal_results[i - 1][K];
            // Need to shift i to match the weight index
            int w = weights[i - 1];
            if (w <= K) {
                int temp_max = optimal_results[i - 1][K - w] + w;
                if (temp_max > max_weight)
                    max_weight = temp_max;
            }
            optimal_results[i][K] = max_weight;
        }
    }
    // display(optimal_results);
    return optimal_results[n][W];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> weights[i];
    }
    std::cout << optimal_weight(W, weights) << '\n';
    // std::cin >> n;
}
