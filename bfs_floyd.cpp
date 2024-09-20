#include <iostream>
#include <vector>
#include <cstdint>

std::vector<size_t> FindCycle(std::vector<size_t>& from, size_t vertex) {

    std::vector<size_t> cycle;

    for (size_t i = from[vertex]; i != vertex; i = from[i]){

        cycle.push_back(i);
    }

    cycle.push_back(vertex);

    return cycle;
}

void dfs(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, 
         std::vector<size_t>& from, std::vector<size_t>& cycle) {

    visited[now] = 1;

    for (size_t neig : graph[now]) {
        if (neig == from[now]) {
            continue;

        } else if (!visited[neig]) {
            
            from[neig] = now;
            dfs(neig, graph, visited, from, cycle);
            if (!cycle.empty()) {
                return;
            }

        } else if (visited[neig] == 1) {
            
            from[neig] = now;
            cycle = FindCycle(from, neig);
            return;
        }
    }

    visited[now] = 2;
}

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

    bool check = true;

    std::vector<std::vector<size_t>> graph(v + 1, std::vector<size_t>(v + 1));

    std::vector<size_t> visited(v + 1);

    std::vector<size_t> from(v + 1);

    std::vector<size_t> cycle;

    MatOfAdj(graph);

    std::vector<std::vector<size_t>> adj_list = ListOfAdj(graph);

    for (size_t i = 1; cycle.empty() && i < adj_list.size(); ++i) {

        if (!visited[i]) {

            dfs(i, adj_list, visited, from, cycle);
        }
    }

    if (!cycle.empty()) {
        
        std::cout << 1;

    } else {

        std::cout << 0;
    }

    return 0;
}
