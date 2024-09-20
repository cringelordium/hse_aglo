#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
private:

    std::vector<int> parent;
    std::vector<int> rank;

public:

    DSU (int n) {

        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    int find(int u) {
    
        if (parent[u] != u)
            parent[u] = find(parent[u]);

        return parent[u];
    }

    void union_sets(int u, int v) {

        int root_u = find(u);
        int root_v = find(v);

        if (root_u == root_v)
            return;

        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        }
            
        else if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
};


struct Edge {

    int start, end, weight;
};


class Kruskal {

private:

    std::vector<Edge> edges;
    size_t V; // Amount of vertex

public:

    Kruskal(int V) : V(V) {
    } 

    void AddEdge(int start, int end, int weight) {
        edges.push_back({start, end, weight});
    }

    int FindMST() {

        std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        DSU dsu(V);

        int min_weight = 0;

        for (const auto& edge : edges) {

            int u = edge.start;
            int v = edge.end;
            int weight = edge.weight;

            int root_u = dsu.find(u);
            int root_v = dsu.find(v);

            if (root_u != root_v) {

                min_weight += weight;
                dsu.union_sets(u, v);
            }
        }
        return min_weight;
    }
};

int main() {
    
    int verticies, edges;
    std::cin >> verticies >> edges;

    Kruskal algo(verticies);

    for (size_t i = 0; i < edges; ++i) {

        int src, dist, weight;
        std::cin >> src >> dist >> weight;

        algo.AddEdge(src, dist, weight);
        
    }

    int answer = algo.FindMST();
    std::cout << answer << std::endl;

    return 0;
}
