#include <iostream>
#include <vector>
#include <set>
#include <climits>

// не работает, 20.04.2024
std::pair<std::vector<size_t>, std::vector<size_t>> FastDijkstra(size_t& start, std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {

    std::vector<size_t> dist(graph.size(), SIZE_MAX);
    std::set<std::pair<size_t, size_t>> sorted_distances;
    std::vector<size_t> from(graph.size(), 0);

    dist[start] = 0;    

    sorted_distances.insert({dist[start], start});

    while (!sorted_distances.empty()) {

        size_t nearest = sorted_distances.begin()->second;
        sorted_distances.erase(sorted_distances.begin());

        for (auto& [neig, trip_time] : graph[nearest]) {

            if (dist[neig] > dist[nearest] + trip_time) {
                
                sorted_distances.erase({dist[neig], neig});
                dist[neig] = dist[nearest] + trip_time;
                sorted_distances.insert({dist[neig], neig});
                
                from[neig] = nearest;

            }
        }
    }

    return {dist, from};
}

void ListOfAdj(std::vector<std::vector<std::pair<size_t, size_t>>>& graph, size_t& routes) {

    for (size_t i = 0; i < routes; ++i) {
        
        size_t location1, location2, cycle_time, trip_time;
        std::cin >> location1 >> location2 >> cycle_time >> trip_time;

        graph[location1].push_back({location2, trip_time});
        graph[location2].push_back({location1, cycle_time}); // добавляем обратное ребро для учёта времени ожидания
    }
}

int main() {

    size_t vertexes;
    std::cin >> vertexes;

    std::vector<std::vector<std::pair<size_t, size_t>>> graph(vertexes + 1);
    
    size_t routes;
    std::cin >> routes;

    ListOfAdj(graph, routes);

    size_t path_length;
    std::cin >> path_length;

    std::vector<size_t> path(path_length);

    for (size_t i = 0; i < path_length; ++i) {
        std::cin >> path[i];
    }

    size_t start = path[0];

    auto [dist, from] = FastDijkstra(start, graph);

    if (dist[path.back()] != SIZE_MAX) {
        std::cout << dist[path.back()] << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}
