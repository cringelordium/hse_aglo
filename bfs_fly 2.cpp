#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>

std::vector<std::vector<size_t>> BFS(std::vector<size_t>& start, std::vector<std::vector<size_t>>& graph, size_t& n, size_t& m) {

    size_t x = start[0];
    size_t y = start[1];

    std::vector<int> x_shift = {1, 2, -1, 2, 1, -2, -1, -2};
    std::vector<int> y_shift = {2, 1, 2, -1, -2, 1, -2, -1};

    std::queue<std::vector<size_t>> queue_of_vertexes;
    std::vector<std::vector<size_t>> dist(n + 4, std::vector<size_t>(m + 4, SIZE_MAX));

    dist[x][y] = 0;
    graph[x][y] = 2;
    queue_of_vertexes.push(start);

    while (!queue_of_vertexes.empty()) {
        
        std::vector<size_t> coordinates = queue_of_vertexes.front();
        queue_of_vertexes.pop();

        size_t x = coordinates[0];
        size_t y = coordinates[1];

        for (size_t i = 0; i < 8; ++i) {

            size_t new_x = x + x_shift[i];
            size_t new_y = y + y_shift[i];

            if (dist[new_x][new_y] > dist[x][y] + 1 && graph[new_x][new_y] != 2) {

                dist[new_x][new_y] = dist[x][y] + 1;

                queue_of_vertexes.push({new_x, new_y});
            }
        }
    }

    return dist;  
}


void MatOfAdj(std::vector<std::vector<size_t>>& graph, size_t& q, size_t& n, size_t& m) {

    const size_t field = 0;

    for (size_t i = 2; i < n + 2; ++i) {
        for(size_t j = 2; j < m + 2; ++j) {

            graph[i][j] = field;
        }
    }

    for (size_t i = 0; i < q; ++i) {
        
        size_t x, y;
        std::cin >> x >> y;

        graph[x + 1][y + 1] = 1;
    }
}

int main() {
    size_t n, m, s, t, q;
    std::cin >> n >> m >> s >> t >> q;

    if (!q) {
        
        std::cout << -1;
    } else {

        std::vector<std::vector<size_t>> graph(n + 4, std::vector<size_t>(m + 4, 2));

        MatOfAdj(graph, q, n, m);

        std::vector<size_t> start = {s + 1, t + 1};

        std::vector<std::vector<size_t>> dist = BFS(start, graph, n, m); 

        size_t sum_of_lengths = 0;

        bool flag = true;

        for (size_t i = 2; i < n + 2; ++i) {
            for (size_t j = 2; j < m + 2; ++j) {

                if (graph[i][j] == 1) {
                    if (dist[i][j] == SIZE_MAX) {
                        
                        flag = false;
                        break;

                    } else {

                        sum_of_lengths += dist[i][j];
                    }
                }
            }
        }

        if (flag) {

            std::cout << sum_of_lengths;
        } else {

            std::cout << -1;
        }

    
    //std::vector<size_t> dist = BFS(start, adj_list);

    // for (const auto& length : dist) {
        
    //     std::cout << length << " "; 
    // }


    // std::cout << v << std::endl;

        // for (size_t i = 0; i < n + 4; ++i) {
        //     for (size_t j = 0; j < m + 4; ++j) {
        //         std::cout << graph[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }

        // for (size_t i = 2; i < n + 2; ++i) {
        //     for (size_t j = 2; j < m + 2; ++j) {
        //         std::cout << dist[i][j] << " ";
        //     }
        //     std::cout << std::endl;
        // }
    }
    return 0;
}
