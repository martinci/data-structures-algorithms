#include <cstdio>
#include <iostream>
#include <string>

const bool DEBUG = true;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    char key;
    // Include size to be able to compute order statistics of the key values.
    int size;
    Vertex *left;
    Vertex *right;
    Vertex *parent;

    Vertex(char key, int size, Vertex *left, Vertex *right, Vertex *parent)
        : key(key), size(size), left(left), right(right), parent(parent) {}
};

void update(Vertex *v) {
    if (v == NULL)
        return;
    v->size = 1 + (v->left != NULL ? v->left->size : 0) + (v->right != NULL ? v->right->size : 0);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex *v) {
    Vertex *parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex *grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex *m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex *m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex *v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex *&root, Vertex *v) {
    if (v == NULL)
        return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Returns the kth element of the splay treee (according to in order traversal)
// k is in [1, size]
Vertex *order_stat(Vertex *&root, int k) {
    Vertex *v = root;
    Vertex *last = root;

    while (v != NULL) {
        int s{0};

        last = v;
        if (v->left != NULL) {
            s = v->left->size;
        }
        if (k == s + 1) {
            // current node is the one
            break;
        } else if (k < s + 1) {
            v = v->left;
        } else {
            v = v->right;
        }
    }

    splay(root, last);
    return v;
}

void split(Vertex *root, int k, Vertex *&left, Vertex *&right) {
    right = order_stat(root, k);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex *merge(Vertex *left, Vertex *right) {
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    Vertex *min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

class Rope {
    std::string s;
    Vertex *root;

    void insert(char c) {
        Vertex *new_vertex = NULL;
        new_vertex = new Vertex(c, 1, NULL, NULL, NULL);
        root = merge(root, new_vertex);
    }

    void traverse_print(Vertex *node) {
        // In order search of the spaly tree
        if (node == NULL) {
            return;
        }
        traverse_print(node->left);
        // output original character
        std::cout << node->key;
        traverse_print(node->right);
    }

  public:
    Rope(const std::string &s) : root(NULL) {
        for (auto ch : s) {
            insert(ch);
        }
    }

    void process(int i, int j, int k) {
        // We use splay trees to edit the string
        Vertex *left = NULL;
        Vertex *middle = NULL;
        Vertex *right = NULL;

        // Cut out s[i..j] into middle
        split(root, j + 2, middle, right);
        split(middle, i + 1, left, middle);
        root = merge(left, right);

        // Open up the string at the kth character, -1 bc we want to insert on the right.
        if (k != 0) {
            split(root, k - 1, left, right);
            root = merge(merge(left, middle), right);
        } else {
            // Special case k=0, prepend middle to the rooot
            root = merge(middle, root);
        }
    }

    void process_slow(int i, int j, int k) {
        std::string t = s.substr(0, i) + s.substr(j + 1);
        s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
    }

    void print() {
        traverse_print(root);
        std::cout << std::endl;
    }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    Rope rope(s);

    rope.print();

    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index) {
        int i, j, k;
        std::cin >> i >> j >> k;
        rope.process(i, j, k);
    }
    rope.print();
}
