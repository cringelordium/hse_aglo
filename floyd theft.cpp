#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <cmath>

void MatOfWeight(std::vector<std::vector<float>>& graph, size_t& edges) {

    for (size_t i = 0; i < edges; ++i) {

        size_t vertex1, vertex2;
        float prob;    
        std::cin >> vertex1 >> vertex2 >> prob;

        if (!prob) {

            graph[vertex1][vertex2] = 1;
            graph[vertex2][vertex1] = 1;

        } else {

            graph[vertex1][vertex2] = 1 - prob / 100;
            graph[vertex2][vertex1] = 1 - prob / 100;

        }
    }

}

void Floyd(std::vector<std::vector<float>>& graph, size_t& vertexes) {

    for (size_t k = 1; k <= vertexes; ++k) {
        for (size_t i = 1; i <= vertexes; ++i) {
            for (size_t j = 1; j <= vertexes; ++j) {
                graph[i][j] = std::max(graph[i][j], graph[i][k] * graph[k][j]);
            }
        }
    }
}

int main() {
    size_t vertexes, edges;
    std::cin >> vertexes >> edges;

    size_t start, end;
    std::cin >> start >> end;

    std::vector<std::vector<float>> graph(vertexes + 1, std::vector<float>(vertexes + 1));

    MatOfWeight(graph, edges);
    Floyd(graph, vertexes);

    for (size_t i = 1; i <= vertexes; ++i) {

        for (size_t j = 1; j <= vertexes; ++j) {
            
            std::cout << graph[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::fixed << std::setprecision(3) << 1 - graph[start][end];

    return 0;
}
