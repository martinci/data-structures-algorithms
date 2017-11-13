#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int hash(const std::string &s) {
    long long p{1000000007};
    int x{23};
    long long m{1000000};
    long long hash{0};
    // hash = sum(s[i] * x^i mod p) mod m
    for (int i = s.size() - 1; i >= 0; --i) {
        hash = (hash * x + s[i]) % p;
    }
    return hash % m;
}

std::vector<int> compute_hashes(const std::string &text, const size_t psize) {
    // Dynamically compute hashes to save time.
    size_t size = text.size() - psize + 1;
    std::vector<int> hashes(size);
    // Initialize last hash
    auto begin = text.begin() + size - 1;
    auto end = text.end();
    std::string last(begin, end);
    // std::cout << last << std::endl;
    hashes[size - 1] = hash(last);
    // Dynamically compute hashes: h_{k-1} = x*h_k + text_{k-1} - text_{k+p-1}*x^p mod p mod m
    long long p{1000000007};
    int x{23};
    long long m{1000000};
    // Precoumpute x^p
    long long x_power_p = 1;
    for (int i = 1; i <= psize; ++i) {
        x_power_p = (x_power_p * x) % p;
    }
    for (int k = (int)size - 1; k > 0; --k) {
        // Debugging cout
        /*for (int j = 0; j < psize; ++j) {
            std::cout << text[k - 1 + j];
        }
        std::cout << " ";*/
        hashes[k - 1] = ((x * hashes[k] + text[k - 1] - text[k + psize - 1] * x_power_p) % p) % m;
        // Normalize mod m value to positive representative.
        hashes[k - 1] = (hashes[k - 1] + m) % m;
        // std::cout << hashes[k - 1] << std::endl;
    }
    return hashes;
}

std::vector<size_t> rabin_karp(const std::string &pattern, const std::string &text) {
    // Rabin-Karp's algorithm for searching pattern in a text
    size_t psize = pattern.size();
    int phash = hash(pattern);
    // std::cout << "phash=" << phash << std::endl;
    auto hashes = compute_hashes(text, psize);

    std::vector<size_t> indexes;
    for (size_t idx = 0; idx < hashes.size(); ++idx) {
        if (hashes[idx] == phash) {
            // Get substring in text to compare
            auto first = text.begin() + idx;
            auto last = text.begin() + idx + psize;
            std::string compare(first, last);
            if (compare == pattern) {
                // Found a match!
                indexes.push_back(idx);
            }
        } else {
            // If hashes are different, substrings can't match. Do nothing.
        }
    }
    return indexes;
}

int main() {
    std::string pattern, text;
    std::cin >> pattern;
    std::cin >> text;
    auto positions = rabin_karp(pattern, text);
    for (auto idx : positions) {
        std::cout << idx << " ";
    }
    std::cout << std::endl;
    return 0;
}
