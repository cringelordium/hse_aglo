#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

std::vector<int> BellmanFord(std::vector<std::vector<int>>& graph, int vertices, int source) {
    std::vector<int> distance(vertices + 1, INT_MAX);
    std::vector<int> from(vertices + 1, -1);

    distance[source] = 0;

    // Run the main algorithm
    for (int i = 1; i <= vertices - 1; ++i) {
        for (int u = 1; u <= vertices; ++u) {
            for (int v = 1; v <= vertices; ++v) {
                if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                    from[v] = u;
                }
            }
        }
    }

    // Check for negative cycles
    std::vector<int> cycle;
    for (int u = 1; u <= vertices; ++u) {
        for (int v = 1; v <= vertices; ++v) {
            if (graph[u][v] != INT_MAX && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v]) {
                // Negative cycle detected, extract the cycle
                int x = v;
                while (!std::count(cycle.begin(), cycle.end(), x)) {
                    cycle.push_back(x);
                    x = from[x];
                }
                cycle.push_back(x); // Add the repeated vertex
                std::reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }

    return cycle; // Return an empty vector if no negative cycle detected
}

int main() {
    int vertices; // Number of vertices in the graph
    std::cin >> vertices;

    std::vector<std::vector<int>> graph(vertices + 1, std::vector<int>(vertices + 1));

    for (int i = 1; i <= vertices; ++i) {
        for(int j = 1; j <= vertices; ++j) {
            std::cin >> graph[i][j];
        }
    }

    std::vector<int> result = BellmanFord(graph, vertices, 1);

    if (result.empty()) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << std::endl;
        std::cout << result.size() << std::endl;
        for (const auto& elem : result) {
            std::cout << elem << " ";
        }
    }

    return 0;
}
