#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int size, parent;

    DisjointSetsElement(int size = 0, int parent = -1) : size(size), parent(parent) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector<DisjointSetsElement> sets;

    DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        // find parent and compress path
        int idx{table};
        if (sets[idx].parent != idx) {
            sets[idx].parent = getParent(sets[idx].parent);
        }
        return sets[idx].parent;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        // std::cout << realDestination << " " << realSource << std::endl;
        if (realDestination != realSource) {
            DisjointSetsElement &source = sets[realSource];
            DisjointSetsElement &destination = sets[realDestination];
            // merge two components
            source.parent = realDestination;
            destination.size += source.size;
            source.size = 0;
            // update max_table_size
            max_table_size = max(max_table_size, destination.size);
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }

    return 0;
}
