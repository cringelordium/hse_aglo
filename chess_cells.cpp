#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>
#include <algorithm>

void dfs(size_t now, std::vector<std::vector<size_t>> &graph, std::vector<bool> &visited) {
    visited[now] = true;

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {

            dfs(neig, graph, visited);
        }
    }
}


int main() {

    size_t v;
    size_t e;

    std::cin >> v >> e; 

    std::vector<std::vector<size_t>> graph(e, std::vector<size_t>(2));
    std::vector<bool> visited(v);

    for (size_t i = 0; i < e; ++i) {

            std::cin >> graph[i][0] >> graph[i][1];
        }

    for (size_t i = 0; i < e; ++i) {
        std::cout << "Ребро " << i + 1 << ": " << graph[i][0] << " -> " << graph[i][1] << std::endl;
    }

}