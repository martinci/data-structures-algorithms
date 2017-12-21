#include <iostream>
#include <set>
#include <stack>
#include <vector>

class Graph {
    std::vector<std::vector<int>> adj;

  public:
    Graph(int n) : adj(n, std::vector<int>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t;
            std::cin >> s >> t;
            // we use 0 index instead of 1 index
            // undirected graph, need to add both adjacencies
            this->adj[s - 1].push_back(t - 1);
            this->adj[t - 1].push_back(s - 1);
        }
    }

    int number_of_components() {
        // explore the graph depth first
        std::set<int> visited;
        int ncomponents = 0;
        // explore nodes until all of them are visited
        while (visited.size() < this->adj.size()) {
            // choose unvisited node (there MUST be at least one)
            int node = 0;
            while (visited.count(node) != 0) {
                node++;
            }
            std::stack<int> to_explore;
            to_explore.push(node);
            // explore connected component
            while (not to_explore.empty()) {
                auto curr = to_explore.top();
                // process current node
                to_explore.pop();
                visited.insert(curr);
                // add unvisited neighbors to to_explore
                for (auto node : this->adj[curr]) {
                    if (visited.count(node) == 0) {
                        to_explore.push(node);
                    }
                }
            }
            ncomponents++;
        }
        return ncomponents;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize maze
    Graph maze(n);
    // read edges
    maze.add_edges(m);

    std::cout << maze.number_of_components() << std::endl;

    return 0;
}
