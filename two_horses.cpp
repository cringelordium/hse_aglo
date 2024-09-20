#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;
using ll = long long;
const ll INF = 1e18;

bool abroad(ll i, ll j) {
    return i >= 1 && i <= 8 && j >= 1 && j <= 8;
}

int main() {
    ll x1, y1, x2, y2, ans = 9999999;
    vector<vector<ll>> d1(9, vector<ll>(9, 0)), d2(9, vector<ll>(9, 0));
    vector<vector<bool>> used1(9, vector<bool> (9)), used2(9, vector<bool> (9));
    ll di[8] = {-2, -2, -1, 1, 2, 2, 1, -1}, dj[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    string a, b;
    cin >> a >> b;
    x1 = ll(a[0] + 1 - 'a');
    y1 = a[1] - '0';
    x2 = ll(b[0] + 1 - 'a');
    y2 = b[1] - '0';

    queue<pair<ll, ll>> q1, q2;
    used1[x1][y1] = true;
    used2[x2][y2] = true;
    q1.push({x1, y1});
    q2.push({x2, y2});
    while (!q1.empty()) {
        ll i = q1.front().first, j = q1.front().second;
        q1.pop();
        for (ll k = 0; k < 8; ++k) {
            ll ito = i + di[k], jto = j + dj[k];
            if (abroad(ito, jto) && !used1[ito][jto]) {
                used1[ito][jto] = true;
                q1.push({ito, jto});
                d1[ito][jto] = d1[i][j] + 1;
            }
        }
    }
    while (!q2.empty()) {
        ll i = q2.front().first, j = q2.front().second;
        if (d1[i][j] == d2[i][j] && d1[i][j] < ans) ans = d1[i][j];
        q2.pop();
        for (ll k = 0; k < 8; ++k) {
            ll ito = i + di[k], jto = j + dj[k];
            if (abroad(ito, jto) && !used2[ito][jto]) {
                used2[ito][jto] = true;
                q2.push({ito, jto});
                d2[ito][jto] = d2[i][j] + 1;
            }
        }
    }

    if (ans == 9999999) cout << -1;
    else cout << ans;

    return 0;
}
