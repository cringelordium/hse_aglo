#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>
#include <algorithm>

void dfs(size_t& now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, size_t& component) {
    visited[now] = component;

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

        if (v1 != v2) {
            graph[v2].push_back(v1);
        }
    }

    for (size_t i = 1; i <= v; ++i) {

        if (graph[i].empty()) {

            graph[i].push_back(i);
        }
    }
}

int main() {

    size_t v;
    size_t e;

    std::cin >> v >> e; 

    std::vector<std::vector<size_t>> graph(v + 1);
    std::vector<size_t> visited(v + 1);

    ListOfAdj(graph, v, e);

    size_t components = 0;

    for (size_t i = 1; i <= v; ++i) {

        if (!visited[i]) {

            components++;
            dfs(i, graph, visited, components);
        }
    }

    std::cout << components << std::endl;

    for (size_t i = 1; i <= components; ++i) {

        std::cout << std::count(visited.begin() + 1, visited.end(), i) << std::endl;

        for (size_t j = 1; j <= visited.size(); ++j) {  

            if (visited[j] == i) {
                std::cout << j << " ";
            }   
        }

        std::cout << std::endl;

    }

    return 0;
}
