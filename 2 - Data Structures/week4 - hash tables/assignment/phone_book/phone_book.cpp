#include <iostream>
#include <string>
#include <vector>

struct Query {
    std::string type, name;
    int number;
};

class PhoneBook {
  private:
    std::vector<std::string> _data;

  public:
    PhoneBook() : _data(1e7) {
        for (int i = 0; i < 1e7; ++i) {
            this->_data[i] = "";
        }
    }

    void add_entry(int number, std::string name) { _data[number] = name; }

    void del_number(int number) { _data[number] = ""; }

    void find(int number) {
        std::string name{_data[number]};
        if (name == "") {
            std::cout << "not found" << std::endl;
        } else {
            std::cout << name << std::endl;
        }
    }
};

std::vector<Query> read_queries() {
    int n;
    std::cin >> n;
    std::vector<Query> queries(n);
    for (auto &query : queries) {
        std::cin >> query.type >> query.number;
        if (query.type == "add") {
            std::cin >> query.name;
        }
    }
    return queries;
}

void process_queries(std::vector<Query> &queries, PhoneBook &pbook) {
    for (auto &query : queries) {
        std::string op = query.type;
        if (op == "add") {
            pbook.add_entry(query.number, query.name);
        } else if (op == "del") {
            pbook.del_number(query.number);
        } else {
            pbook.find(query.number);
        }
    }
}

void display(std::vector<Query> queries) {
    for (auto query : queries) {
        std::cout << query.type << "\t" << query.number << "\t" << query.name << std::endl;
    }
}

int main() {
    std::vector<Query> queries = read_queries();
    // display(queries);
    PhoneBook pbook;
    process_queries(queries, pbook);
    return 0;
}
