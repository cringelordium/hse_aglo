#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>
#include <set>

void ListOfAdj(std::vector<std::vector<std::pair<size_t, size_t>>>& graph, size_t& edges) {

    for (size_t i = 1; i <= edges; ++i) {

        size_t vertex1, vertex2, weight;
        std::cin >> vertex1 >> vertex2 >> weight;

        graph[vertex1].push_back(std::make_pair(vertex2, weight));
        graph[vertex2].push_back(std::make_pair(vertex1, weight));

    }
}

//O((V + E)logV)
std::pair<std::vector<size_t>, std::vector<size_t>> FastDijkstra(size_t& start, std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {

    std::vector<size_t> dist(graph.size(), SIZE_MAX);
    std::set<std::pair<size_t, size_t>> sorted_distances;
    std::vector<size_t> from(graph.size(), 0);

    dist[start] = 0;    

    sorted_distances.insert({dist[start], start});

    while (!sorted_distances.empty()) {

        size_t nearest = sorted_distances.begin()->second;
        sorted_distances.erase(sorted_distances.begin());

        for (auto& [neig, weight] : graph[nearest]) {

            if (dist[neig] > dist[nearest] + weight) {
                
                sorted_distances.erase({dist[neig], neig});
                dist[neig] = dist[nearest] + weight;
                sorted_distances.insert({dist[neig], neig});
                
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

    size_t vertexes, edges;
    std::cin >> vertexes >> edges;

    std::vector<std::vector<std::pair<size_t, size_t>>> graph(vertexes + 1);

    ListOfAdj(graph, edges);

    size_t start, end;
    std::cin >> start >> end;

    if (edges) {
        
        auto res = FastDijkstra(start, graph);

        std::vector<size_t> dist = res.first;

        if (dist[end] != SIZE_MAX) {
            
            std::cout << dist[end] << std::endl;

            std::vector<size_t> from = res.second;

            std::vector<size_t> path = GetPath(from, end);

            std::cout << path.size() << std::endl;

            for(const auto& elem : path) {

                std::cout << elem << " ";
            }

        } else {

            std::cout << -1;
        }
    } else {
        
        if (start == end) {
            std::cout << 0;
        } else {
            std::cout << -1;
        }

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
