#include <iostream>
#include <vector>
#include <limits>
#include <climits>
#include <algorithm>

std::vector<int> BellmanFord(std::vector<std::vector<int>>& graph, int vertices, int source) {

    std::vector<int> distance(vertices + 1, INT_MAX);
    std::vector<int> from(vertices + 1, -1);

    std::vector<int> cycle;

    distance[source] = 0;
    
    for (int i = 0; i <= vertices - 1; ++i) {
        for (int i = 1; i <= vertices; ++i) {
            for (int j = 1; j <= vertices; ++j) {

                if (distance[j] > distance[i] + graph[i][j]) {
                    distance[j] = distance[i] + graph[i][j];
                    from[j] = i;
                }
            }
        }
    }

    for (int i = 1; i <= vertices; ++i) {
        for (int j = 1; j <= vertices; ++j) {

            if (distance[j] > distance[i] + graph[i][j]) {

                for (int l = 1; l <= vertices - 1; ++l) {

                    j = from[j];

                }

                i = j;

                while (i != from[j]) {
                    
                    cycle.push_back(j);
                    j = from[j];
                }

                std::reverse(cycle.begin(), cycle.end());
                break;
                
            }
        } 
    }

    return cycle;
}

int main() {

    int vertices; // Number of vertices in the graph
    std::cin >> vertices;
    
    int source = 1;   // Source vertex

    std::vector<std::vector<int>> graph(vertices + 1, std::vector<int>(vertices + 1));

    for (int i = 1; i <= vertices; ++i) {
        for(int j = 1; j <= vertices; ++j) {

            std::cin >> graph[i][j];
        }
    }

    std::vector<int> result = BellmanFord(graph, vertices, source);

    if (result.empty()) {

        std::cout << "NO";
    } else {

        std::cout << "YES" << std::endl;

        std::cout << result.size() << std::endl;
        
        for (const auto& elem : result) {

            std::cout << elem << " ";
        }
    }
        
    return 0;
}
