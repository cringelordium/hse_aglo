#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>

 std::vector<size_t> ReturnPath(std::vector<size_t>& from, size_t& end_vertex) {
    
    std::vector<size_t> path;

    for (size_t vertex = end_vertex; vertex != -1; vertex = from[vertex])

        path.push_back(vertex);

    std::reverse(path.begin(), path.end());

    return path;
}

std::pair<std::vector<size_t>, std::vector<size_t>> BFS(size_t now, std::vector<std::vector<size_t>>& graph) {

    const size_t max_size = 1e9;

    std::queue<size_t> queue_of_vertexes;
    std::vector<size_t> dist(graph.size(), max_size);
    std::vector<size_t> from(graph.size(), -1);

    dist[now] = 0;
    queue_of_vertexes.push(now);

    while(!queue_of_vertexes.empty()) {
        
        size_t vertex = queue_of_vertexes.front();
        queue_of_vertexes.pop();

        for (size_t neig : graph[vertex]) {

            if (dist[neig] > dist[vertex] + 1) {

                dist[neig] = dist[vertex] + 1;
                from[neig] = vertex;
                queue_of_vertexes.push(neig);
            }
        }
    }

    return {dist, from};
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

    std::vector<std::vector<size_t>> graph(v + 1, std::vector<size_t>(v + 1));

    std::vector<size_t> visited(v + 1);

    MatOfAdj(graph);

    std::vector<std::vector<size_t>> adj_list = ListOfAdj(graph);

    size_t start, end;
    std::cin >> start >> end;

    std::pair<std::vector<size_t>, std::vector<size_t>> result = BFS(start, adj_list);

    std::vector<size_t> dist = result.first;

    std::vector<size_t> path = ReturnPath(result.second, end);

    if (dist[end] != 1e9) {

        std::cout << dist[end] << std::endl;

        if (dist[end]) {

            for (const auto& vertex : path) {

                std::cout << vertex << " ";
            }
        }
    } else {

        std::cout << -1 << std::endl;
    }

    // std::cout << v << std::endl;

    // for (size_t i = 1; i < graph.size(); ++i) {
    //     for (size_t j = 1; j < graph.size(); ++j) {
    //         std::cout << graph[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // for (size_t i = 1; i < adj_list.size(); ++i) {

    //     std::cout << i << std::endl;

    //     for (auto& num : adj_list[i]) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << std::endl;
    // }
    
    return 0;
}
