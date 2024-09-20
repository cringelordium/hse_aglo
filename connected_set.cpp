#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

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

    int start, end;
    float weight;
};

struct Point {
    
    int x;
    int y;
};

class Kruskal {

private:

    std::unordered_map<int, Point> points;
    std::vector<Edge> edges;
    size_t V; // Amount of vertex

public:

    Kruskal(int V) : V(V) {
    } 

    void AddPoint(int idx, int x, int y) {
        points[idx] = {x, y};
    }

    void AddEdge(int start, int end, float weight) {

        if (!weight) {

            weight = GetWeight(start, end);
        }

        edges.push_back({start, end, weight});
    }

    float GetWeight(int start, int end) {

        return sqrt((points[start].x - points[end].x) * (points[start].x - points[end].x) + 
                    (points[start].y - points[end].y) * (points[start].y - points[end].y));
    }

    std::vector<int> Make;

    float FindMST() {

        std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        DSU dsu(V);

        for (auto& pair : points) {

            dsu.union_sets(pair.second.x, pair.second.y);
        }

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
    
    
    size_t amount_of_point; 
    std::cin >> amount_of_point;

    Kruskal algo(amount_of_point);

    for (size_t i = 1; i <= amount_of_point; ++i) {
        
        int x, y;
        std::cin >> x >> y;
        algo.AddPoint(i, x, y);
    }

    size_t edges;
    std::cin >> edges;

    DSU ds(amount_of_point);

    for (size_t i = 1; i <= edges; ++i) {

        int u, v;
        std::cin >> u >> v;

        algo.AddPoint(i, u, v);
        
    }

    for (int i = 1; i <= amount_of_point; ++i) {
        for (int j = i + 1; i <= amount_of_point; ++j) {

            algo.AddEdge(i, j, 0);
        }
    }

    int min_tree_now = algo.FindMST();      

    return 0;
}
