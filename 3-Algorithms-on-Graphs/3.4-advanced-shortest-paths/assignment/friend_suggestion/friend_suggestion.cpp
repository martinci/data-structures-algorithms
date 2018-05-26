#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

const bool DEBUG = false;

const long long INFINITY = std::numeric_limits<long long>::max() / 4;

// Weighted directed graph class
class WeightedDiGraph {
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> weights;

  public:
    WeightedDiGraph(int n) : adj(n, std::vector<int>()), weights(n, std::vector<int>()) {}

    void add_edges(const int m) {
        for (int j = 0; j < m; ++j) {
            int s, t, w;
            std::cin >> s >> t >> w;
            // we use 0 index instead of 1 index
            this->adj[s - 1].push_back(t - 1);
            this->weights[s - 1].push_back(w);
        }
    }

    long long distance(const int s, const int t) {
        // implement bidirectional Dijkstra
        long long dist{0};
        return dist;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    // initialize graph
    WeightedDiGraph graph(n);
    // read edges
    graph.add_edges(m);

    // query the graph for distances
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int s, t;
        std::cin >> s >> t;
        std::cout << graph.distance(s, t) << std::endl;
    }
    return 0;
}
