#include <iostream>
#include <vector>
#include <limits>
#include <climits>

void BellmanFord(int vertices, int source) {

    std::vector<int> distance(vertices + 1, INT_MAX);
    
    distance[source] = 0;

    for (int i = 1; i <= vertices; ++i) {
        for(int j = i + 1; j <= vertices; ++j) {

            if (distance[j] > distance[i] + ((179*i + 719*j) % 1000) - 500) {
                distance[j] = distance[i] + ((179*i + 719*j) % 1000) - 500;
            }
        }
    }

    std::cout << distance[vertices] << std::endl;
}

int main() {

    int vertices; // Number of vertices in the graph
    std::cin >> vertices;
    
    int source = 1;   // Source vertex

    BellmanFord(vertices, source);

    return 0;
}
