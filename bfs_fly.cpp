#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>

std::vector<std::vector<std::pair<size_t,int>>> make_graph(const size_t& n) {
    std::vector<std::vector<std::pair<size_t,int>>> graph(n);
    for (int to = 2; to <= n; ++to) {
        for (int from = 1; from < to; ++from) {
            graph[from].push_back({to, (179*from + 719*to) % 1000 - 500});
        }
    }
    return graph;
}

void fordbellman(std::vector<std::vector<std::pair<size_t,int>>>& graph, std::vector<int>& dist, size_t v) {
    for (size_t i = 1; i <= v; ++i) {
        for (auto para : graph[i]) {
            auto j = para.first;
            auto len = para.second;
            dist[j] = std::min(dist[j],dist[i]+len);
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;
    auto graph = make_graph(n);
    std::vector<int> dist(n+1,1000000000);
    dist[1] = 0;
    fordbellman(graph,dist,n);
    std::cout << dist[n];
    return 0;
}
