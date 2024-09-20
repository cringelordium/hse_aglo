#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>
#include <queue>
#include <numeric>
#include <set>

void EdgeRemover(std::vector<std::vector<size_t>>& graph, std::pair<size_t, size_t>& edge) {

    if (graph[edge.first][edge.second] && graph[edge.second][edge.first]) {

        graph[edge.first][edge.second] = 0;
        graph[edge.second][edge.first] = 0;
    }
}

 void FindAllPaths(std::vector<std::vector<int>>& from, size_t end_vertex, std::pair<size_t, size_t>& edge, std::vector<std::vector<size_t>>& graph) {

    if (end_vertex == -1) {
        return;
    }

    for (auto parent : from[end_vertex]) {
        if (parent != -1) {
            edge = std::make_pair(end_vertex, parent);
            EdgeRemover(graph, edge);
            FindAllPaths(from, parent, edge, graph);
        }
    }
}

void BFS(size_t now, std::vector<std::vector<size_t>>& graph, std::vector<std::vector<int>>& from) {

    std::queue<size_t> queue_of_vertexes;
    std::vector<size_t> dist(graph.size(), SIZE_MAX);

    dist[now] = 0;
    from[now] = { -1 };
    queue_of_vertexes.push(now);

    while(!queue_of_vertexes.empty()) {
        
        size_t vertex = queue_of_vertexes.front();
        queue_of_vertexes.pop();

        for (size_t neig = 1; neig < graph.size(); ++neig) {
             
            if (graph[vertex][neig] && dist[neig] > dist[vertex] + 1) {

                dist[neig] = dist[vertex] + 1;

                from[neig].clear();
                from[neig].push_back(vertex);
                queue_of_vertexes.push(neig);

            } else if (graph[vertex][neig] && dist[neig] == dist[vertex] + 1) {
                
                from[neig].push_back(vertex);
            }
        }
    }
}


void ListsOfAdj(std::vector<std::vector<std::pair<size_t, size_t>>>& graph, size_t& edges) {

    for (size_t i = 0; i < edges; ++i) {

        size_t vert1, vert2;
        std::cin >> vert1 >> vert2;
        
        if (graph[vert1])
        graph[vert1].push_back[]  
        }
    }

}

size_t EdgeCounter(std::vector<std::vector<size_t>>& graph) {
    
    size_t ones = 0;

    for (size_t i = 1; i < graph.size(); ++i) {

        ones += std::accumulate(graph[i].begin(), graph[i].end(), 0);
    }

    return ones / 2;
}

int main() {

    size_t vertexes, edges;
    std::cin >> vertexes >> edges;

    std::vector<std::vector<size_t>> graph(vertexes + 1);
    size_t multiple_edges = 0;

    MatOfAdj(graph, edges);

    size_t start, end;
    std::cin >> start >> end;

    std::vector<std::vector<int>> from(vertexes + 1);    

    BFS(start, graph, from);

    std::pair<size_t, size_t> edge;

    FindAllPaths(from, end, edge, graph);

    std::cout << EdgeCounter(graph) << std::endl;

    return 0;
}
