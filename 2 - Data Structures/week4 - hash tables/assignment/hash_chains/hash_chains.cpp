#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct Query {
    std::string type, s;
    size_t idx;
};

class HashTable {
  private:
    std::vector<std::list<std::string>> _buckets;
    int _m; // number of buckets for the hash table

    int _hash(std::string s) {
        long long p{1000000007};
        int x{263};
        long long hash{0};
        // hash = sum(s[i] * x^i mod p) mod m
        for (int i = s.size() - 1; i >= 0; --i) {
            hash = (hash * x + s[i]) % p;
        }
        return hash % this->_m;
    }

    bool _find_in_list(std::list<std::string> &lst, std::string s) {
        // Try to find s in the list
        auto it = std::find(lst.begin(), lst.end(), s);
        return it != lst.end();
    }

  public:
    HashTable(int size) : _buckets(size), _m(size) {}

    void add(std::string s) {
        int hvalue = _hash(s);
        auto &lst = _buckets[hvalue];
        bool found = _find_in_list(lst, s);
        if (not found) {
            lst.push_front(s);
        }
    }

    void del(std::string s) {
        int hvalue = _hash(s);
        auto &lst = _buckets[hvalue];
        auto it = std::find(lst.begin(), lst.end(), s);
        if (it != lst.end()) {
            lst.erase(it);
        }
    }

    void find(std::string s) {
        int hvalue = _hash(s);
        auto &lst = _buckets[hvalue];
        bool found = _find_in_list(lst, s);
        std::cout << (found ? "yes" : "no") << std::endl;
    }

    void check(size_t idx) {
        auto &lst = _buckets[idx];
        for (auto &e : lst) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
};

std::vector<Query> read_queries() {
    int n;
    std::cin >> n;
    std::vector<Query> queries(n);
    for (auto &query : queries) {
        std::cin >> query.type;
        if (query.type == "check") {
            std::cin >> query.idx;
        } else {
            std::cin >> query.s;
        }
    }
    return queries;
}

void process_queries(std::vector<Query> &queries, HashTable &table) {
    for (auto &query : queries) {
        std::string op = query.type;
        if (op == "add") {
            table.add(query.s);
        } else if (op == "del") {
            table.del(query.s);
        } else if (op == "find") {
            table.find(query.s);
        } else {
            table.check(query.idx);
        }
    }
}

void display(std::vector<Query> queries) {
    for (auto query : queries) {
        std::cout << query.type << "\t" << query.s << "\t" << query.idx << std::endl;
    }
}

int main() {
    int m;
    std::cin >> m;
    HashTable table(m);
    std::vector<Query> queries = read_queries();
    // display(queries);
    process_queries(queries, table);
    return 0;
}
