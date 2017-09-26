#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool lex_comp(string a, string b) {
    /* Performs lexicographic comparison  a >= b with a twist.
       If one is shorte we must recursively compare with the other. */
    size_t min = std::min(a.size(), b.size());

    for (size_t i = 0; i < min; ++i) {
        int diff = a[i] - b[i];
        if (diff > 0)
            return true;
        if (diff < 0)
            return false;
    }

    // Same head of the string. Compare extra chars, if any, with the first of a.
    int delta = a.size() - b.size();
    if (delta == 0) {
        return true;

    } else if (delta > 0) {
        // Compare rest of a with b
        string rest_a = "";
        for (size_t i = b.size(); i < a.size(); ++i) {
            rest_a += a[i];
        }
        return lex_comp(rest_a, b);

    } else {
        // Compare the rest of b with a
        string rest_b = "";
        for (size_t i = a.size(); i < b.size(); ++i) {
            rest_b += b[i];
        }
        return lex_comp(a, rest_b);
    }
}

size_t get_largest_string(vector<string> a) {
    string max{a[0]};
    size_t idx{0};
    for (size_t i = 1; i < a.size(); ++i) {
        if (lex_comp(a[i], max)) {
            max = a[i];
            idx = i;
        }
    }
    return idx;
}

string largest_number(vector<string> a) {
    std::stringstream ret;
    while (not a.empty()) {
        size_t idx = get_largest_string(a);
        ret << a[idx];
        a.erase(a.begin() + idx);
    }
    string result;
    ret >> result;
    return result;
}

string largest_number_naive(vector<string> a) {
    string max{"-1"};
    do {
        std::stringstream ret;
        for (auto &str : a) {
            ret << str;
        }
        string number;
        ret >> number;
        if (std::stoll(number) >= std::stoll(max)) {
            max = number;
        }
    } while (std::next_permutation(a.begin(), a.end()));
    return max;
}

void test_lex_comp() {
    int n, m;
    for (int i = 0; i < 100; i++) {
        n = rand() % 1000 + 1;
        m = rand() % 1000 + 1;
        std::cout << n << "\t" << m << std::endl;
        std::cout << lex_comp(std::to_string(n), std::to_string(m)) << std::endl;
    }
}

void test_solution() {
    while (true) {
        int n = rand() % 5 + 1;
        vector<string> a;
        for (int i = 0; i < n; i++) {
            a.push_back(std::to_string(rand() % 1000 + 1));
        }
        string res1 = largest_number(a);
        string res2 = largest_number_naive(a);
        if (res1 == res2) {
            std::cout << "OK!" << std::endl;
        } else {
            std::cout << "Wrong answer!" << std::endl;
            for (auto &str : a) {
                std::cout << str << " ";
            }
            std::cout << std::endl;
            std::cout << res1 << "\t" << res2;
            break;
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
    // test_solution();
    // test_lex_comp();
    std::cin >> n;
}
