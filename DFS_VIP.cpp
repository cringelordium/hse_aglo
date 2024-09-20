#include <iostream>
#include <vector>
#include <cstdint>

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, int color, bool& check) {
    visited[now] = color;

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {

            dfs(neig, graph, visited, 3 - color, check);

        } else if (visited[neig] == color) {
            
            check = false;

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

    std::vector<size_t> visited(v + 1);

    ListOfAdj(graph, v, e);

    bool check = true;

    for (size_t l = 1; l <= v; ++l) {
        if (!visited[l]) {

            dfs(l, graph, visited, 1, check);
        }
    }

    if (check) {

        std::cout << "YES" << std::endl;

        for (size_t i = 1; i < visited.size(); ++i) {
            
            if (visited[i] == 2) {
                std::cout << i << " ";
            } 
        }

        std::cout << std::endl;

        for (size_t i = 1; i < visited.size(); ++i) {
            
            if (visited[i] == 2) {
                std::cout << i << " ";
            } 
        }

    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
