#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position) : type(type), position(position) {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack<Bracket> opening_brackets_stack;
    int idx{0};
    bool broken{false};
    for (; idx < (int)text.size(); ++idx) {
        auto next = text[idx];
        if (next == '(' || next == '[' || next == '{') {
            Bracket lbracket{next, idx};
            opening_brackets_stack.push(lbracket);
        }
        if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.empty()) {
                // 1st priority case: unmatched closing bracket.
                broken = true;
                break;
            } else {
                auto top = opening_brackets_stack.top();
                opening_brackets_stack.pop();
                if (not top.Matchc(next)) {
                    // 2nd priority case: closing the wrong opening bracket.
                    broken = true;
                    break;
                }
            }
        }
    }

    if (broken) {
        std::cout << idx + 1 << std::endl;
    } else if (opening_brackets_stack.empty()) {
        std::cout << "Success" << std::endl;
    } else {
        auto top = opening_brackets_stack.top();
        std::cout << top.position + 1 << std::endl;
    }

    return 0;
}
