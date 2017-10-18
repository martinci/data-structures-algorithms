#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

class Node;

class Node {
  public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() { this->parent = NULL; }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int get_height(Node *root) {
    int max_height{0};
    std::stack<std::pair<Node *, int>> node_stack;
    node_stack.push({root, 1});

    while (not node_stack.empty()) {
        auto pair = node_stack.top();
        Node *node = pair.first;
        int curr_height = pair.second;
        node_stack.pop();
        if (node->children.empty()) {
            // We reached a leaf, compute height and go back to parent.
            max_height = std::max(max_height, curr_height);
        } else {
            // Add children to stack
            for (auto &child : node->children) {
                node_stack.push({child, curr_height + 1});
            }
        }
    }
    return max_height;
}

int naive_get_height(std::vector<Node> nodes) {
    int maxHeight = 0;
    for (int leaf_index = 0; leaf_index < (int)nodes.size(); leaf_index++) {
        int height = 0;
        for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
            height++;
        maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
}

int main(int argc, char **argv) {
    int n;
    std::cin >> n;

    std::vector<Node> nodes;
    nodes.resize(n);
    Node *root;
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0) {
            nodes[child_index].setParent(&nodes[parent_index]);
        } else {
            // found the root node
            root = &nodes[child_index];
        }
        nodes[child_index].key = child_index;
    }

    // std::cout << root->key << std::endl;

    auto maxHeight = get_height(root);
    std::cout << maxHeight << std::endl;
    return 0;
}
