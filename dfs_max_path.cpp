#include <iostream>
#include <vector>
#include <algorithm>

void dfs_find_bridges(size_t v, size_t parent, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& tin, std::vector<size_t>& low, std::vector<bool>& visited, size_t& timer, std::vector<std::vector<size_t>>& bridges) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (size_t u : graph[v]) {
        if (u == parent) continue;
        if (visited[u]) {
            low[v] = std::min(low[v], tin[u]);
        } else {
            dfs_find_bridges(u, v, graph, tin, low, visited, timer, bridges);
            low[v] = std::min(low[v], low[u]);
            if (low[u] > tin[v]) {
                bridges.push_back({v, u});
            }
        }
    }
}

void dfs_find_distances(size_t v, size_t parent, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& max_distances, std::vector<bool>& visited, size_t& max_distance) {
    visited[v] = true;
    std::vector<size_t> child_distances;
    for (size_t u : graph[v]) {
        if (u == parent) continue;
        if (!visited[u]) {
            dfs_find_distances(u, v, graph, max_distances, visited, max_distance);
        }
        child_distances.push_back(max_distances[u]);
    }
    std::sort(child_distances.begin(), child_distances.end(), std::greater<size_t>());
    if (child_distances.size() >= 2) {
        max_distance = std::max(max_distance, child_distances[0] + child_distances[1] + 1);
    }
    if (!child_distances.empty()) {
        max_distances[v] = child_distances[0] + 1;
    }
}

int main() {
    size_t N;
    std::cin >> N;
    
    std::vector<std::vector<size_t>> graph(N + 1);
    std::vector<size_t> tin(N + 1), low(N + 1), max_distances(N + 1);
    std::vector<bool> visited(N + 1, false);
    std::vector<std::vector<size_t>> bridges;

    for (size_t i = 0; i < N - 1; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    size_t timer = 0;
    for (size_t i = 1; i <= N; ++i) {
        if (!visited[i]) {
            dfs_find_bridges(i, 0, graph, tin, low, visited, timer, bridges);
        }
    }

    size_t max_distance = 0;
    std::fill(visited.begin(), visited.end(), false);
    dfs_find_distances(1, 0, graph, max_distances, visited, max_distance);

    std::cout << max_distance << std::endl;

    return 0;
}
