#include <cstdio>
#include <iostream>
#include <string>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    int key;
    int size;
    Vertex *left;
    Vertex *right;
    Vertex *parent;

    Vertex(int key, int size, Vertex *left, Vertex *right, Vertex *parent)
        : key(key), size(size), left(left), right(right), parent(parent) {}
};

void update(Vertex *v) {
    if (v == NULL)
        return;
    v->size = 1 + (v->left != NULL ? v->left->size : 0) + (v->right != NULL ? v->right->size : 0);
    ;
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

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex *find(Vertex *&root, int key) {
    Vertex *v = root;
    Vertex *last = root;
    Vertex *next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex *root, int key, Vertex *&left, Vertex *&right) {
    right = find(root, key);
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
    Vertex *root = NULL;

    void insert(int idx) {
        Vertex *left = NULL;
        Vertex *right = NULL;
        Vertex *new_vertex = NULL;
        split(root, idx, left, right);
        if (right == NULL || right->key != idx) {
            new_vertex = new Vertex(idx, 1, NULL, NULL, NULL);
        }
        root = merge(merge(left, new_vertex), right);
    }

    Vertex *get_kth_char(Vertex *root, int k) {
        int s = root->left->size;
        if (k == s + 1) {
            return root;
        } else if (k < s + 1) {
            return get_kth_char(root->left, k);
        } else {
            return get_kth_char(root->right, k);
        }
    }

  public:
    Rope(const std::string &s) : s(s) {
        for (int idx = 0; idx < s.size(); ++idx) {
            insert(idx);
        }
    }

    void process(int i, int j, int k) {
        // Replace this code with a faster implementation
        Vertex *left = NULL;
        Vertex *middle = NULL;
        Vertex *right = NULL;
        split(root, i, left, middle);
        split(middle, j + 1, middle, right);
        root = merge(left, right);
        auto node = get_kth_char(root, k);
        split(root, node->key, left, right);
    }

    void process_slow(int i, int j, int k) {
        // Replace this code with a faster implementation
        std::string t = s.substr(0, i) + s.substr(j + 1);
        s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
    }

    std::string result() { return s; }
};

int main() {
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    Rope rope(s);
    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index) {
        int i, j, k;
        std::cin >> i >> j >> k;
        rope.process(i, j, k);
    }
    std::cout << rope.result() << std::endl;
}
