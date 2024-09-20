#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>

void MatOfAdj(std::vector<std::vector<int>>& graph) {

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {

            std::cin >> graph[i][j];  
        }
    }
}

std::vector<std::vector<std::pair<size_t, size_t>>> ListOfAdj(std::vector<std::vector<int>>& graph) {

    std::vector<std::vector<std::pair<size_t, size_t>>> list_of_adj(graph.size());

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {
            
            if (graph[i][j] != -1) {
                auto vert_weight = std::make_pair(j, graph[i][j]);
                list_of_adj[i].push_back(vert_weight);
            }
        }
    }
    
    return list_of_adj;
}

std::pair<std::vector<size_t>, std::vector<size_t>> Dijkstra(size_t& start, std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {

    const size_t max_dist = 1e9;
    std::vector<size_t> dist(graph.size(), 1e9);
    std::vector<size_t> visited(graph.size(), 0);
    std::vector<size_t> from(graph.size());

    std::queue<std::pair<size_t, size_t>> vertexes_check;

    dist[start] = 0;    
    
    for (size_t i = 1; i < graph.size(); ++i) {

        int nearest = -1;
        for (size_t vertex = 1; vertex < graph.size(); ++vertex) {
            
            if (!visited[vertex] && ( nearest == -1 || dist[nearest] > dist[vertex])) {

                nearest = vertex;
            }
        }

        visited[nearest] = 1;

        for (auto &[neig, weight] : graph[nearest]) {

            if (dist[neig] > dist[nearest] + weight) {

                dist[neig] = dist[nearest] + weight;

                from[neig] = nearest;
            }
        }
    }

    return {dist, from};
} 

std::vector<size_t> GetPath(std::vector<size_t>& from, size_t& end) {

    std::vector<size_t> path;
    for(size_t vertex = end; vertex != 0; vertex = from[vertex]) {

        path.push_back(vertex);
    }

    std::reverse(path.begin(), path.end());

    return path;
} 

int main() {

    size_t vertexes, start, end;;
    std::cin >> vertexes >> start >> end;

    std::vector<std::vector<int>> graph(vertexes + 1, std::vector<int>(vertexes + 1));

    std::vector<size_t> dist(vertexes + 1);
    std::vector<size_t> from;

    MatOfAdj(graph);

    auto ListsOfAdj = ListOfAdj(graph);
    auto res = Dijkstra(start, ListsOfAdj);

    dist = res.first;
    from = res.second;

    if (dist[end] != 1e9) {
        
        std::vector<size_t> path = GetPath(from, end);

        for (const auto& vertex : path) {

            std::cout << vertex << " ";
        }

    } else {

        std::cout << -1;
    }

    // if (dist[end] != 1e9) {

    //     std::cout << dist[end] << std::endl;

    //     if (dist[end]) {

    //         for (const auto& vertex : path) {

    //             std::cout << vertex << " ";
    //         }
    //     }
    // } else {

    //     std::cout << -1 << std::endl;
    // }

    // std::cout << v << std::endl;

    // for (size_t i = 1; i < graph.size(); ++i) {
    //     for (size_t j = 1; j < graph.size(); ++j) {

    //         std::cout << graph[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    return 0;
}
