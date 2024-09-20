#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>
#include <climits>
#include <set>

void ListOfAdj(std::vector<std::vector<std::pair<size_t, size_t>>>& graph, size_t& edges) {

    for (size_t i = 1; i <= edges; ++i) {

        size_t vertex1, vertex2, weight;
        std::cin >> vertex1 >> vertex2 >> weight;

        graph[vertex1].push_back(std::make_pair(vertex2, weight));
        graph[vertex2].push_back(std::make_pair(vertex1, weight));

    }
}

//O((V + E)logV)
std::pair<std::vector<size_t>, std::set<std::pair<size_t, size_t>>> FastDijkstra(size_t& start, std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {

    std::vector<size_t> dist(graph.size(), SIZE_MAX);
    std::set<std::pair<size_t, size_t>> sorted_distances;

    std::set<std::pair<size_t, size_t>> saved_distances;
    std::vector<size_t> from(graph.size(), 0);

    dist[start] = 0;

    sorted_distances.insert({dist[start], start});

    while (!sorted_distances.empty()) {

        size_t nearest = sorted_distances.begin()->second;
        sorted_distances.erase(sorted_distances.begin());

        for (auto& [neig, weight] : graph[nearest]) {

            if (dist[neig] > dist[nearest] + weight) {
                
                sorted_distances.erase({dist[neig], neig});
                dist[neig] = dist[nearest] + weight;
                sorted_distances.insert({dist[neig], neig});
                
                saved_distances.insert({dist[neig], neig});
            }
        }
    }

    return {dist, saved_distances};
}

void CityOrValley(std::vector<bool>& city_check, size_t& cities) {

    for (size_t i = 0; i < cities; ++i) {

        size_t city_idx;
        std::cin >> city_idx;

        city_check[city_idx] = true; 
    }
}

int main() {

    size_t localities, roads, cities, capital_idx; // Населенные пункты (города и деревни), дороги, города, и номер столицы
    std::cin >> localities >> roads >> cities >> capital_idx;

    std::vector<bool>city_check (localities + 1, false);
    CityOrValley(city_check, cities);

    std::vector<std::vector<std::pair<size_t, size_t>>> graph(localities + 1);
    ListOfAdj(graph, roads);

    auto res = FastDijkstra(capital_idx, graph);
    std::vector<size_t> dist = res.first;
    std::set<std::pair<size_t, size_t>> saved_dists;

    for (size_t i = 1; i < city_check.size(); ++i) {

        if (city_check[i]) {

            saved_dists.insert({dist[i], i});
        }
    }

    for (auto& [distance, idx] : saved_dists) {

        std::cout << idx << " " << distance << std::endl;
    }
    
    return 0;
}
