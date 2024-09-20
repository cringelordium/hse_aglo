#include <iostream>
#include <vector>
#include <cstdint>
#include <stack>
#include <algorithm>
#include <map>

void DFS(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited, 
            std::vector<std::vector<size_t>>& orient_graph, std::vector<size_t>& topsort) {

    visited[now] = 1;

    for (size_t neig : graph[now]) {

        if (!visited[neig]) {
            
            DFS(neig, graph, visited, orient_graph, topsort);
        }

        orient_graph[neig].push_back(now);

    }

    topsort.push_back(now);
    visited[now] = 2;
}

void DFS_Components(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<size_t>& visited_2, std::vector<size_t>& colors) {

    visited_2[now] = 1;

    for (size_t neig : graph[now]) {
        if (visited_2[neig]) {

            DFS_Components(neig, graph, visited_2, colors);
        }
        
    }

    visited_2[now] = 2;
}

void ListOfAdj(std::vector<std::vector<size_t>>& graph, const size_t& e, std::map<size_t, std::vector<size_t>>& edge_order) {

    for (size_t i = 0; i < e; ++i) {

        size_t v1, v2;
        std::cin >> v1 >> v2;
        
        graph[v1].push_back(v2);

        edge_order[i].push_back(v1);
        edge_order[i].push_back(v2);
    }
}

int main() {
    size_t v, e;
    std::cin >> v >> e;

    bool check = false;

    std::vector<std::vector<size_t>> graph(v + 1);

    std::vector<std::vector<size_t>> orient_graph(v + 1);

    std::vector<size_t> visited(v + 1);

    std::vector<size_t> visited_2(v + 1);

    std::vector<size_t> topsort;

    std::map<size_t, std::vector<size_t>> edge_order;

    ListOfAdj(graph, e, edge_order);
    
    for (size_t i = 1; i < graph.size(); ++i) {

        if(!visited[i]) {

            DFS(i, graph, visited, orient_graph, topsort);
        }
    }

    std::reverse(topsort.begin(), topsort.end());

    std::vector<size_t> colors(v + 1);

    for (const auto& vertex : topsort) {
        
        DFS_Components(vertex, orient_graph, visited_2, colors);
    }

    // Вывод топсорта
    for (size_t i = 0; i < v; ++i) {

        std::cout << topsort[i] << " ";
    }

    std::cout << std::endl;

    //Вывод ориентированного графа
    for (size_t i = 1; i < orient_graph.size(); ++i) {

        std::cout << i << std::endl;

        for (auto& num : orient_graph[i]) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    for (auto it = edge_order.begin(); it != edge_order.end(); ++it) {
        // it->first - ключ
        // it->second - значение
        std::cout << "Key: " << (it->first) + 1 << std::endl;

        for (const auto& vertex : it->second) {

            std:: cout << vertex << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
