#include <iostream>
#include <string>
#include <vector>

using std::string;
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

int edit_distance(const string &str1, const string &str2) {
    // Create a matrix for dynamic programming
    size_t m = str1.size();
    size_t n = str2.size();
    vector<vector<size_t>> distance(m + 1);
    for (auto &row : distance)
        row.resize(n + 1);

    // Initialize distance matrix
    for (size_t i = 0; i <= m; ++i)
        distance[i][0] = i;
    for (size_t j = 0; j <= n; ++j)
        distance[0][j] = j;

    for (size_t j = 1; j <= n; ++j) {
        for (size_t i = 1; i <= m; ++i) {
            int min = distance[i][j - 1] + 1;
            int temp_min = distance[i - 1][j] + 1;
            if (temp_min < min)
                min = temp_min;
            // Subtract 1 to make index match
            if (str1[i - 1] != str2[j - 1]) {
                temp_min = distance[i - 1][j - 1] + 1;
            } else {
                temp_min = distance[i - 1][j - 1];
            }
            if (temp_min < min)
                min = temp_min;
            distance[i][j] = min;
        }
    }
    // display(distance);
    return distance[m][n];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    // std::cin >> str1;
    return 0;
}
