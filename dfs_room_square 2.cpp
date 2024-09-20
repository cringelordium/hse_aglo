#include <iostream>
#include <vector>
#include <cstdint>


void dfs(int x, int y, std::vector<std::vector<char>>& graph, std::vector<std::vector<size_t>>& visited, size_t& count_of_cells) {

    if (visited[x][y] || graph[x][y] == '*') {
        return;
    }
    
    visited[x][y] = 1;
    count_of_cells++;

    // Сдвиги для движения вокруг текущей клетки (вверх, вниз, влево, вправо)
    std::vector<int> x_shift = {-1, 1, 0, 0};
    std::vector<int> y_shift = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {

        int nx = x + x_shift[i];
        int ny = y + y_shift[i];

        dfs(nx, ny, graph, visited, count_of_cells);
    }
}

int main() {
    size_t lab_size;
    std::cin >> lab_size;

    std::vector<std::vector<char>> graph(lab_size + 1, std::vector<char>(lab_size + 1));

    for (size_t i = 1; i <= lab_size; ++i) {
        for (size_t j = 1; j <= lab_size; ++j) {
            std::cin >> graph[i][j];
        }
    }

    size_t x, y;
    std::cin >> x >> y; 

    std::vector<std::vector<size_t>> visited(lab_size + 1, std::vector<size_t>(lab_size + 1, 0));

    size_t count_of_cells = 0;

    dfs(x, y, graph, visited, count_of_cells);

    std::cout << count_of_cells << std::endl;

    return 0;
}
