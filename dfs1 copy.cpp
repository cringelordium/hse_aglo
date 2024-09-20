#include <iostream>
#include <vector>
#include <cstdint>

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<bool>& visited, std::vector<size_t>& component) {
    visited[now] = true;
    component.push_back(now);

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            dfs(neig, graph, visited, component);
        }
    }
}

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& v, const size_t& e) {
    for (size_t i = 0; i < e; ++i) {
        size_t v1, v2;
        std::cin >> v1 >> v2;
        
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

int main() {
    size_t v, e;
    std::cin >> v >> e;

    std::vector<std::vector<size_t>> graph(v + 1);
    std::vector<bool> visited(v + 1, false);

    ListOfAdj(graph, v, e);

    size_t components = 0;
    std::vector<std::vector<size_t>> componentVertices;

    for (size_t i = 1; i <= v; ++i) {
        if (!visited[i]) {
            components++;
            std::vector<size_t> component;
            dfs(i, graph, visited, component);
            componentVertices.push_back(component);
        }
    }

    std::cout << components << std::endl;

    for (const auto& comp : componentVertices) {
        std::cout << comp.size() << std::endl;
        for (size_t vertex : comp) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
