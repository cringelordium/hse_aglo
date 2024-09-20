#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> tin, low;
vector<bool> visited;
int timer = 0;
unordered_set<int> bridges;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : graph[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.insert(v);
                bridges.insert(to);
            }
        }
    }
}

int dfs_max_depth(int v, vector<vector<int>>& new_graph) {
    visited[v] = true;
    int max_depth = 0;
    for (int to : new_graph[v]) {
        if (!visited[to]) {
            max_depth = max(max_depth, dfs_max_depth(to, new_graph));
        }
    }
    return max_depth + 1;
}

int main() {
    int n;
    cin >> n;

    graph.resize(n);
    tin.resize(n);
    low.resize(n);
    visited.resize(n, false);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    vector<vector<int>> new_graph(n);
    for (int v = 0; v < n; ++v) {
        for (int u : graph[v]) {
            if (bridges.count(v) == 0 || bridges.count(u) == 0) {
                new_graph[v].push_back(u);
            }
        }
    }

    int max_distance = 0;
    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            max_distance = max(max_distance, dfs_max_depth(i, new_graph));
        }
    }

    cout << max_distance << endl;

    return 0;
}
