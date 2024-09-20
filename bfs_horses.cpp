#include <iostream>
#include <queue>
#include <utility> // Для std::pair и std::make_pair

// Проверка, находится ли клетка на шахматной доске
bool isValid(int x, int y) {
    return (x >= 1 && x <= 8 && y >= 1 && y <= 8);
}

// Функция для нахождения количества шагов для коней до достижения общей клетки
int minStepsForKnights(std::pair<int, int> start1, std::pair<int, int> start2) {
    // Возможные ходы коней
    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

    // Очереди для BFS для каждого коня
    std::queue<std::pair<std::pair<int, int>, int>> q1;
    std::queue<std::pair<std::pair<int, int>, int>> q2;

    // Массивы для отслеживания посещенных клеток и количества шагов
    int visited1[9][9] = {0};
    int visited2[9][9] = {0};

    // Помечаем стартовые клетки коней и добавляем их в очереди
    q1.push(std::make_pair(start1, 0));
    q2.push(std::make_pair(start2, 0));
    visited1[start1.first][start1.second] = 1;
    visited2[start2.first][start2.second] = 1;

    while (!q1.empty()) {
        std::pair<std::pair<int, int>, int> current1 = q1.front();
        q1.pop();
        std::pair<std::pair<int, int>, int> current2 = q2.front();
        q2.pop();

        int x1 = current1.first.first;
        int y1 = current1.first.second;
        int steps1 = current1.second;

        int x2 = current2.first.first;
        int y2 = current2.first.second;
        int steps2 = current2.second;

        // Проверяем, достигли ли мы общей клетки
        if (visited1[x2][y2] || visited2[x1][y1]) {
            return steps1 + steps2;
        }

        // Перебираем все возможные ходы коней и добавляем их в очереди
        for (int i = 0; i < 8; ++i) {
            int newX1 = x1 + dx[i];
            int newY1 = y1 + dy[i];
            int newX2 = x2 + dx[i];
            int newY2 = y2 + dy[i];

            if (isValid(newX1, newY1) && !visited1[newX1][newY1]) {
                visited1[newX1][newY1] = 1;
                q1.push(std::make_pair(std::make_pair(newX1, newY1), steps1 + 1));
            }

            if (isValid(newX2, newY2) && !visited2[newX2][newY2]) {
                visited2[newX2][newY2] = 1;
                q2.push(std::make_pair(std::make_pair(newX2, newY2), steps2 + 1));
            }
        }
    }

    // Если кони не могут достичь общей клетки
    return -1;
}


int main() {

    std::string positions;
    std::getline(std::cin, positions);

    int x1 = positions[0] - 'a' + 1; 
    int y1 = positions[1] - '1' + 1;

    int x2 = positions[3] - 'a' + 1; 
    int y2 = positions[4] - '1' + 1;

    std::cout << x1 << y1 << x2 << y2;

    std::pair<int, int> start1 = std::make_pair(x1, y1);
    std::pair<int, int> start2 = std::make_pair(x2, y2);

    int steps = minStepsForKnights(start1, start2);

    std::cout << steps;

    return 0;
}
