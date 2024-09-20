#include <iostream>
#include <vector>
#include <cstdint>

void MatOfWeight(std::vector<std::vector<int>>& graph) {

    for (size_t i = 1; i < graph.size(); ++i) {
        for (size_t j = 1; j < graph.size(); ++j) {

            std::cin >> graph[i][j];
        }
    }

}

void Floyd(std::vector<std::vector<int>>& graph, size_t& vertexes) {

    for (size_t k = 1; k <= vertexes; k++) {
        for (size_t i = 1; i <= vertexes; i++) {
            for (size_t j = 1; j <= vertexes; j++) {

                if (graph[i][j] > graph[i][k] + graph[k][j]) {

                    graph[i][j] = graph[i][k] + graph[k][j]; 
                }
            }
        }
    }
}

int main() {
    size_t vertexes;
    std::cin >> vertexes;

    std::vector<std::vector<int>> graph(vertexes + 1, std::vector<int>(vertexes + 1));

    MatOfWeight(graph);

    Floyd(graph, vertexes);

    // for (size_t i = 1; i <= vertexes; ++i) {

    //     for (size_t j = 1; j <= vertexes; ++j) {
            
    //         std::cout << graph[i][j] << " ";
    //     }

    //     std::cout << std::endl;
    // }

    int max_element = graph[1][1];

    for (size_t i = 1; i <= vertexes; ++i) {
        for (size_t j = 1; j <= vertexes; ++j) {
            if (graph[i][j] > max_element) {
                max_element = graph[i][j];
            }
        }
    }

    std::cout << max_element;

    return 0;
}
