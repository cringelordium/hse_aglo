#include <iostream>
#include <vector>
#include <cstdint>
#include <stack>
#include <algorithm>

void dfs_top(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& vis2, std::vector<size_t>& topsort) {

    vis2[now] = 1;

    for (size_t neig : graph[now]) {
        if (!vis2[neig]) {
            
            dfs_top(neig, graph, vis2, topsort);
        }
    }

    vis2[now] = 2;
    topsort.push_back(now);
}

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, bool& CycleCheck) {

    visited[now] = 1;

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {
            
            dfs(neig, graph, visited, CycleCheck);

        } else if (visited[neig] == 1) {
            
            CycleCheck = true;
        }
    }

    visited[now] = 2;
}

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& vertexes) {

    for (size_t i = 1; i <= vertexes; ++i) {

        size_t req_doctors;
        std::cin >> req_doctors;
        
        for (size_t j = 0; j < req_doctors; ++j) {
            
            size_t vertex;
            std::cin >> vertex;
            graph[vertex].push_back(i);
        }
    }
}

int main() {
    size_t vertexes;
    std::cin >> vertexes;

    bool check = false;

    std::vector<std::vector<size_t>> graph(vertexes + 1);

    std::vector<size_t> visited(vertexes + 1);

    std::vector<size_t> vis2(vertexes + 1);

    std::vector<size_t> topsort;

    ListOfAdj(graph, vertexes);

    for (size_t i = 1; i < graph.size(); ++i) {

        if (!visited[i]) {

            dfs(i, graph, visited, check);
        }
    }

    if (check) {
        
        std::cout << -1 << std::endl;

    } else {

        for (size_t i = 1; i < graph.size(); ++i) {

            if (!vis2[i]) {

                dfs_top(i, graph, vis2, topsort);
            }
        }

        std::reverse(topsort.begin(), topsort.end());

        for (const auto& elem : topsort) {

            std::cout << elem << " ";
        }
    }
    
    return 0;
}