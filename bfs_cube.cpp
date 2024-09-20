#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>

template <typename T>
using cube = std::vector<std::vector<std::vector<T>>>;

std::vector<std::vector<size_t>> BFS(std::pair<size_t>& start, cube<size_t>& graph, size_t& vertex) {

    const size_t max_size = 1e9;
    std::vector<std::vector<size_t>> dist(vertex + 2, std::vector<size_t>(vertex + 2));

    size_t x = start[0];
    size_t y = start[1];

    std::vector<int> x_shift = {-1, 1, 0, 0};
    std::vector<int> y_shift = {0, 0, -1, 1};

    std::queue<std::vector<size_t>> queue_of_vertexes;

    dist[x][y] = 0;
    queue_of_vertexes.push(start);

    while(!queue_of_vertexes.empty()) {
        
        std::vector<size_t> coordinates = queue_of_vertexes.front();
        queue_of_vertexes.pop();

        size_t x = coordinates[0];
        size_t y = coordinates[1];

        for (size_t i = 0; i < 4; ++i) {

            size_t new_x = x + x_shift[i];
            size_t new_y = y + y_shift[i];

            if (dist[new_x][new_y] > dist[x][y] + 1 && graph[new_x][new_y] != 1) {

                dist[new_x][new_y] = dist[x][y] + 1;

                queue_of_vertexes.push({new_x, new_y});
            }
        }
    }

    return dist;  
}


std::vector<std::pair<size_t, size_t>> MatOfAdj(size_t& l, size_t& w, std::vector<std::vector<size_t>>& graph) {

    std::vector<std::pair<size_t, size_t>> starts;

    for (size_t i = 1; i <= l; ++i) {
        for (size_t j = 1; j <= w; ++j) {
                
            size_t symbol;
            std::cin >> symbol;
            graph[i][j] = symbol;

            if (symbol == 1) {

                starts.push_back({i, j});
            }
        
        }
    }

    return starts;
}

int main() {

    size_t l, w;
    std::cin >> l >> w;
    
    std::vector<std::vector<size_t>> graph(l + 2, std::vector<size_t>(w + 2));
    auto result = MatOfAdj(l, w, graph);

    std::vector<std::vector<size_t>> dist = BFS(start, graph, v);

    size_t min_value = dist[1][1][1];
    for (size_t i = 1; i <= v; ++i) {
        for (size_t j = 1; j <= v; ++j) {

            min_value = std::min(min_value, dist[1][i][j]);
        }
    }

    std::cout << min_value << std::endl;
    
    return 0;
}
