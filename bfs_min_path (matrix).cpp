#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>
#include <queue>

 std::vector<size_t> ReturnPath(std::vector<size_t>& from, size_t& end_vertex) {
    
    std::vector<size_t> path;

    for (size_t vertex = end_vertex; vertex != -1; vertex = from[vertex])

        path.push_back(vertex);

    std::reverse(path.begin(), path.end());

    return path;
}

std::pair<std::vector<size_t>, std::vector<size_t>> BFS(size_t now, std::vector<std::vector<size_t>>& graph) {

    std::queue<size_t> queue_of_vertexes;
    std::vector<size_t> dist(graph.size(), SIZE_MAX);
    std::vector<size_t> from(graph.size(), -1);

    dist[now] = 0;
    queue_of_vertexes.push(now);

    while(!queue_of_vertexes.empty()) {
        
        size_t vertex = queue_of_vertexes.front();
        queue_of_vertexes.pop();

        for (size_t neig = 1; neig < graph.size(); ++neig) {
             
            if (graph[vertex][neig] && dist[neig] > dist[vertex] + 1) {

                dist[neig] = dist[vertex] + 1;
                from[neig] = vertex;
                queue_of_vertexes.push(neig);
            }
        }
    }

    return {dist, from};
}


void MatOfAdj(std::vector<std::vector<size_t>>& graph, size_t& edges) {

    for (size_t i = 0; i < edges; ++i) {

        size_t vert1, vert2;
        std::cin >> vert1 >> vert2;
        
        if (!graph[vert1][vert2] && !graph[vert2][vert1]) {
            
            graph[vert1][vert2] = 1;
            graph[vert2][vert1] = 1;
        } else {

            ++graph[vert1][vert2];
            ++graph[vert2][vert1];     
        }
    }
}

void RemoveEdges(std::vector<std::vector<size_t>>& matrix_adj, const std::vector<std::pair<size_t, size_t>>& edgesToRemove, size_t& vertexes) {

    for (const auto& edge : edgesToRemove) {
        size_t vert1 = edge.first;
        size_t vert2 = edge.second;

        if (matrix_adj[vert1][vert2] == 1 && matrix_adj[vert2][vert1] == 1) {

            matrix_adj[vert1][vert2] = 0;
            matrix_adj[vert2][vert1] = 0;
        } else {

            --matrix_adj[vert1][vert2];
            --matrix_adj[vert2][vert1];     
        }
    }
}

int main() {

    size_t v, e;
    std::cin >> v >> e;

    std::vector<std::vector<size_t>> graph(v + 1, std::vector<size_t>(v + 1, 0));

    MatOfAdj(graph, e);

    size_t start, end;
    std::cin >> start >> end;

    std::pair<std::vector<size_t>, std::vector<size_t>> result = BFS(start, graph);
    std::vector<size_t> dist = result.first;
    std::vector<size_t> path = ReturnPath(result.second, end);

    size_t current_min_path = dist[end];
    size_t min_path_edges = 0;

    for (size_t i = 1; i < path.size(); ++i) {
        size_t u = path[i - 1];
        size_t v = path[i];

        if (graph[u][v] > 1) {
            // Ребро повторяется, удаляем только одно вхождение
            --graph[u][v];
            --graph[v][u];
            --min_path_edges;
        } else {
            // Проверяем, остается ли T достижимой
            graph[u][v] = graph[v][u] = 0; // Удаляем ребро
            std::pair<std::vector<size_t>, std::vector<size_t>> result1 = BFS(start, graph);
            if (result1.first[end] == SIZE_MAX) {
                // T недостижима, возвращаем ребро
                ++graph[u][v];
                ++graph[v][u];
                ++min_path_edges;
            }
        }
    }


    std::cout << e - min_path_edges << std::endl;

    return 0;
}
