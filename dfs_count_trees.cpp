#include <iostream>
#include <vector>
#include <cstdint>

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited) {
    visited[now] = 1;

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            dfs(neig, graph, visited);
        }
    }

    visited[now] = 2;
}

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& v) {
    for (size_t i = 1; i < v; ++i) {
        size_t v1, v2;
        std::cin >> v1 >> v2;
        
        if (v1 < v2) {
            graph[v1].push_back(v2);
        } else {
            graph[v2].push_back(v1);
        }
    }
}

int main() {
    size_t v;
    std::cin >> v;

    std::vector<std::vector<size_t>> graph(v + 1);

    std::vector<size_t> result(v + 1, 0);

    ListOfAdj(graph, v);

    for (size_t i = 1; i <= v; ++i) {

        std::vector<size_t> visited(v + 1, 0);
        dfs(i, graph, visited);

        for (size_t j = 1; j < visited.size(); ++j) {
            if (visited[j] == 2) {

                ++result[i];    
            }
        }
    }

    for (size_t i = 1; i < result.size(); ++i) {
        
        std::cout << result[i] << " ";
    }

    return 0;
}
