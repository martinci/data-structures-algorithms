#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

class Graph {
    std::vector<std::vector<int>> _adj;

  public:
    Graph(int n) : _adj(n, std::vector<int>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t;
            std::cin >> s >> t;
            // we use 0 index instead of 1 index
            // undirected graph, need to add both adjacencies
            this->_adj[s - 1].push_back(t - 1);
            this->_adj[t - 1].push_back(s - 1);
        }
    }

    bool are_connected(const int s, const int t) {
        // explore the graph depth first
        std::set<int> visited;
        std::stack<int> to_explore;
        to_explore.push(s);

        while (not to_explore.empty()) {
            auto curr = to_explore.top();
            if (curr == t) {
                return true;
            }
            // process current node
            to_explore.pop();
            visited.insert(curr);
            // add unvisited neighbors to to_explore
            for (auto node : this->_adj[curr]) {
                if (visited.count(node) == 0) {
                    to_explore.push(node);
                }
            }
        }
        // we couldn't find t
        return false;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize maze
    Graph maze(n);
    // read edges
    maze.add_edges(m);
    // are u and v connected?
    int u, v;
    std::cin >> u >> v;
    // we use 0-index
    std::cout << maze.are_connected(u - 1, v - 1) << std::endl;

    return 0;
}
