#include <iostream>
#include <vector>

// DFS с подсчётом размера поддерева
size_t dfs(size_t now, const std::vector<std::vector<size_t>>& graph, std::vector<bool>& visited, std::vector<size_t>& subtree_sizes) {
    visited[now] = true;
    size_t size = 1; // Учитываем текущую вершину

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            size += dfs(neig, graph, visited, subtree_sizes);
        }
    }

    subtree_sizes[now] = size;
    return size;
}

int main() {
    size_t v;
    std::cin >> v;

    std::vector<std::vector<size_t>> graph(v + 1); // +1 для учёта вершины 1 как корня дерева
    std::vector<size_t> subtree_sizes(v + 1); // Размеры поддеревьев для каждой вершины
    std::vector<bool> visited(v + 1, false);

    // Считываем рёбра и строим граф
    for (size_t i = 1; i < v; ++i) {
        size_t v1, v2;
        std::cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    // Выполняем DFS, начиная с вершины 1, и подсчитываем размеры поддеревьев
    dfs(1, graph, visited, subtree_sizes);

    for (size_t i = 1; i <= v; ++i) {
        std::cout << subtree_sizes[i] << " ";
    }

    return 0;
}
