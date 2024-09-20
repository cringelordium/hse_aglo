#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>
#include <algorithm>

void dfs(size_t& now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, 
         std::vector<size_t>& tin, std::vector<size_t>& tout, size_t& time) {

    visited[now] = 1;
    ++time;
    tin[now] = time;

    for (size_t neig : graph[now]) {
        if (!visited[neig]) {

            dfs(neig, graph, visited, tin, tout, time);

        } 
    }
    
    visited[now] = 2;
    ++time;
    tout[now] = time;
    
}

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& v, const size_t& e) {
    
    for (size_t i = 0; i < e; ++i) {

        size_t v1, v2;
        std::cin >> v1 >> v2;

        if (v1 != v2) {
            graph[v2].push_back(v1);    
        }
    }

}

int main() {

    size_t v;
    size_t e;

    std::cin >> v >> e; 

    std::vector<std::vector<size_t>> graph(v + 1);
    std::vector<size_t> visited(v + 1);

    std::vector<size_t> tin(v + 1);
    std::vector<size_t> tout(v + 1);
    size_t time = 0;

    ListOfAdj(graph, v, e);

    // for (size_t i = 1; i <= v; ++i) {

    //     if (!visited[i]) {

    //         dfs(1, graph, visited, tin, tout, time);
    //     }
    // }

    size_t target = 1;

    dfs(target, graph, visited, tin, tout, time);

    // for (size_t i = 1; i < graph.size(); ++i) {
        
    //     std::cout << i << std::endl;

    //     for (auto& num : graph[i]) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }

    std::vector<size_t> ans;

    for (size_t i = 1; i < graph.size(); ++i) {
        
        if (visited[i] == 2) {
            
            ans.push_back(i);
        }
    }

    std::sort(ans.begin(), ans.end());

    for (const auto& ver : ans) {
        
        std::cout << ver << " ";
    }

    return 0;
}
