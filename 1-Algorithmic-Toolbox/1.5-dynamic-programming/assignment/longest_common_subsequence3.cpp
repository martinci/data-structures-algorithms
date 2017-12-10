#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

// Helper function to output a matrix in the console.
template <class T> void display(vector<vector<T>> &matrix) {
    for (auto &row : matrix) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Helper function to output a vector in the console
template <class T> void display(vector<T> &vec) {
    for (auto &v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

// lcs2 is very similar to the edit distance from problem 3
vector<vector<size_t>> max_alignment_scores(vector<int> &a, vector<int> &b) {
    // Create a matrix for dynamic programming
    size_t m = a.size();
    size_t n = b.size();
    vector<vector<size_t>> scores(m + 1);
    for (auto &row : scores)
        row.resize(n + 1);

    // Initialize scores matrix, redundant because by default they are initialized to 0.
    for (size_t i = 0; i <= m; ++i)
        scores[i][0] = 0;
    for (size_t j = 0; j <= n; ++j)
        scores[0][j] = 0;

    for (size_t j = 1; j <= n; ++j) {
        for (size_t i = 1; i <= m; ++i) {
            int max = scores[i][j - 1];
            int temp_max = scores[i - 1][j];
            if (temp_max > max)
                max = temp_max;
            // Subtract 1 to make index match
            if (a[i - 1] != b[j - 1]) {
                temp_max = scores[i - 1][j - 1];
            } else {
                temp_max = scores[i - 1][j - 1] + 1;
            }
            if (temp_max > max)
                max = temp_max;
            scores[i][j] = max;
        }
    }
    // display(scores);
    return scores;
}

vector<int> output_lcs(vector<int> &a, vector<int> &b) {
    auto scores = max_alignment_scores(a, b);
    vector<int> sequence;
    size_t i = a.size();
    size_t j = b.size();
    while (i > 0 or j > 0) {
        if (i > 0 and scores[i][j] == scores[i - 1][j]) {
            --i;
        } else if (j > 0 and scores[i][j] == scores[i][j - 1]) {
            --j;
        } else {
            if (a[i - 1] == b[j - 1])
                sequence.push_back(a[i - 1]);
            --i;
            --j;
        }
    }
    // display(scores);
    return sequence;
}

size_t max_alignment_score(vector<int> &a, vector<int> &b, vector<int> &c) {
    // Create a matrix for dynamic programming
    size_t m = a.size();
    size_t n = b.size();
    size_t l = c.size();
    vector<vector<vector<size_t>>> scores(m + 1);
    for (auto &row : scores) {
        row.resize(n + 1);
        for (auto &col : row) {
            col.resize(l + 1);
        }
    }
    // scores is initialized to 0s by default.
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            for (size_t k = 1; k <= l; ++k) {
                vector<size_t> options(7);
                options.push_back(scores[i][j - 1][k - 1]);
                options.push_back(scores[i - 1][j][k - 1]);
                options.push_back(scores[i - 1][j - 1][k]);
                options.push_back(scores[i][j][k - 1]);
                options.push_back(scores[i][j - 1][k]);
                options.push_back(scores[i - 1][j][k]);
                // Subtract 1 to make index match
                if (a[i - 1] == b[j - 1] and b[j - 1] == c[k - 1]) {
                    options.push_back(scores[i - 1][j - 1][k - 1] + 1);
                } else {
                    options.push_back(scores[i - 1][j - 1][k - 1]);
                }
                scores[i][j][k] = *std::max_element(options.begin(), options.end());
            }
        }
    }
    return scores[m][n][l];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << max_alignment_score(a, b, c) << std::endl;
    // auto scores = max_alignment_scores(a, b);
    // display(scores);
    // std::cin >> an;
}
