#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Flight {
    int departure;
    int destination;
    int departure_time;
    int arrival_time;
};

const int INF = INT_MAX;

int main() {
    int N, A, B, K;
    cin >> N >> A >> B >> K;

    vector<Flight> flights(K);
    for (int i = 0; i < K; ++i) {
        cin >> flights[i].departure >> flights[i].departure_time >> flights[i].destination >> flights[i].arrival_time;
    }

    vector<int> arrival_time(N + 1, INF);
    arrival_time[A] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < K; ++j) {
            int u = flights[j].departure;
            int v = flights[j].destination;
            int departure_time = flights[j].departure_time;
            int flight_time = flights[j].arrival_time - departure_time;

            if (arrival_time[u] != INF && arrival_time[u] <= departure_time) {
                arrival_time[v] = min(arrival_time[v], flights[j].arrival_time);
            }
        }
    }

    cout << arrival_time[B] << endl;

    return 0;
}
