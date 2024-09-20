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

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& e) {

    for (size_t i = 0; i < e; ++i) {

        size_t v1, v2;
        std::cin >> v1 >> v2;
        
        graph[v1].push_back(v2);
    }
}

int main() {
    size_t v, e;
    std::cin >> v >> e;

    bool check = false;

    std::vector<std::vector<size_t>> graph(v + 1);

    std::vector<size_t> visited(v + 1);

    std::vector<size_t> vis2(v + 1);

    std::vector<size_t> topsort;

    ListOfAdj(graph, e);

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
