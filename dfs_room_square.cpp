#include <iostream>
#include <vector>
#include <cstdint>
#include <stack>
#include <algorithm>
#include <map>


void MatOfAdj(std::vector<std::vector<size_t>>& graph) {

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {

            std::cin >> graph[i][j];
        }
    }

}

std::vector<std::vector<size_t>> ListOfAdj(std::vector<std::vector<size_t>>& graph) {

    std::vector<std::vector<size_t>> list_of_adj(graph.size());

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {
            
            if (graph[i][j]) {
                
                list_of_adj[i].push_back(j);
            }
        }
    }
    
    return list_of_adj;
}

int main() {
    size_t v;
    std::cin >> v;

    std::vector<std::vector<size_t>> graph(v + 1, std::vector<size_t>(v + 1));

    std::vector<size_t> visited(v + 1);

    std::vector<size_t> from(v + 1);

    std::vector<size_t> cycle;

    MatOfAdj(graph);

    std::vector<std::vector<size_t>> adj_list = ListOfAdj(graph);

    std::cout << v << std::endl;

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (size_t i = 1; i < adj_list.size(); ++i) {

        std::cout << i << std::endl;

        for (auto& num : adj_list[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
