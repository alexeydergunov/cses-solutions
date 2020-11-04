#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int ans = INF;
        auto bfs = [&](const int start) {
            vector<int> d(n, INF);
            d[start] = 0;
            queue<ii> q;
            q.emplace(start, -1);
            while (!q.empty()) {
                const auto [x, p] = q.front(); q.pop();
                for (const int y : g[x]) {
                    if (y == p) {
                        continue;
                    }
                    if (d[y] > d[x] + 1) {
                        d[y] = d[x] + 1;
                        q.emplace(y, x);
                    } else {
                        ans = min(ans, d[x] + d[y] + 1);
                    }
                }
            }
        };
        for (int start = 0; start < n; start++) {
            bfs(start);
        }

        if (ans == INF) {
            ans = -1;
        }
        cout << ans << '\n';
    }
}
