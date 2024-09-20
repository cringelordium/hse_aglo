#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>

// работает (хз почему, устал) 20.04.2024
void ListOfAdj(std::vector<std::vector<std::tuple<size_t, size_t, size_t>>>& graph, size_t& routes) {

    for (size_t i = 0; i < routes; ++i) {
        
        size_t valley1, start_time, valley2, end_time;
        std::cin >> valley1 >> start_time >> valley2 >> end_time;

        auto route = std::make_tuple(valley2, start_time, end_time);
        graph[valley1].push_back(route);
    }
}

std::pair<std::vector<size_t>, std::vector<size_t>> Dijkstra(size_t& start, std::vector<std::vector<std::tuple<size_t, size_t, size_t>>>& graph) {

    std::vector<size_t> dist_time(graph.size(), SIZE_MAX);
    std::vector<size_t> now_time(graph.size(), SIZE_MAX);
    std::vector<size_t> visited(graph.size(), 0);

    std::priority_queue<std::tuple<size_t, size_t, size_t>> pq;

    dist_time[start] = 0;
    now_time[start] = 0;
    pq.push({0, 0, start});

    while (!pq.empty()) {
        auto [time, current_time, current] = pq.top();
        pq.pop();

        if (visited[current]) continue;
        visited[current] = 1;

        for (auto &[neig, start_time, end_time] : graph[current]) {

            if (current_time <= start_time && now_time[neig] > end_time) {

                now_time[neig] = end_time;
                dist_time[neig] = start_time - current_time + end_time;
                pq.push({-dist_time[neig], now_time[neig], neig});
            }
        }
    }

    return {now_time, dist_time};
} 


std::vector<size_t> GetPath(std::vector<size_t>& from, size_t& end) {

    std::vector<size_t> path;
    for(size_t vertex = end; vertex != 0; vertex = from[vertex]) {

        path.push_back(vertex);
    }

    std::reverse(path.begin(), path.end());

    return path;
} 

int main() {

    size_t vertexes;
    std::cin >> vertexes;

    std::vector<std::vector <std::tuple<size_t, size_t, size_t>>> graph(vertexes + 1);
    
    size_t start_valley, end_valley;
    std::cin >> start_valley >> end_valley;

    size_t routes;
    std::cin >> routes;

    ListOfAdj(graph, routes);
    
    if (start_valley != end_valley) {

        std::vector<size_t> dist = Dijkstra(start_valley, graph).first;
        std::vector<size_t> dist2 = Dijkstra(start_valley, graph).second;

        if (dist[end_valley] != SIZE_MAX) {

            std::cout << dist[end_valley] << std::endl;

            // for (size_t i = 1; i < dist.size(); ++i) {

            //     std::cout << dist[i] << " ";
            // }

            // std::cout << std::endl;

            // for (size_t i = 1; i < dist2.size(); ++i) {

            //     std::cout << dist2[i] << " ";
            // }

        } else {

            std::cout << -1;
        }
    } else {

        std::cout << 0;
    }

    
    return 0;
}
