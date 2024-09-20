#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; // Значение "бесконечности"

void floyd_warshall(vector<vector<int>>& dist, int n) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    // Инициализация матрицы расстояний
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    // Заполнение матрицы начальными расстояниями
    for (int i = 0; i < m; ++i) {
        int bi, ei, wi;
        cin >> bi >> ei >> wi;
        dist[bi][ei] = wi; // Предполагаемое изменение веса Роджера
    }

    // Алгоритм Флойда-Уоршелла
    floyd_warshall(dist, n);

    // Ввод номеров городов, где проводятся концерты
    vector<int> concerts(k);
    for (int i = 0; i < k; ++i) {
        cin >> concerts[i];
    }

    // Проверка наличия бесконечного увеличения веса Роджера
    bool infinite = false;
    for (int i = 0; i < k - 1; ++i) {
        if (dist[concerts[i]][concerts[i + 1]] == INF) {
            infinite = true;
            break;
        }
    }

    if (infinite) {
        cout << "infinitely kind" << endl;
    } else {
        // Вывод количества рейсов и номеров используемых рейсов
        int num_flights = k - 1;
        cout << num_flights << endl;
        for (int i = 0; i < num_flights; ++i) {
            cout << dist[concerts[i]][concerts[i + 1]] << " ";
        }
        cout << endl;
    }

    return 0;
}
