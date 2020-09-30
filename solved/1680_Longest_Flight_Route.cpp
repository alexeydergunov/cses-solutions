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
        vector<int> inDeg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            inDeg[y]++;
        }

        vector<int> dp(n, -INF);
        vector<int> parent(n, -1);
        dp[0] = 0;
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDeg[i] == 0) {
                q.push(i); // even if we start from -INF vertices, we will process vertex 0 eventually
            }
        }
        while (!q.empty()) {
            const int x = q.front(); q.pop();
            for (const int y : g[x]) {
                if (dp[x] >= 0) { // update only if we are not in -INF vertex now
                    if (dp[y] < dp[x] + 1) {
                        dp[y] = dp[x] + 1;
                        parent[y] = x;
                    }
                }
                inDeg[y]--;
                if (inDeg[y] == 0) {
                    q.push(y);
                }
            }
        }

        if (dp[n - 1] < 0) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }
        assert(dp[n - 1] >= 0);

        vector<int> path;
        int x = n - 1;
        while (true) {
            path.push_back(x);
            if (x == 0) break;
            x = parent[x];
        }
        reverse(all(path));

        cout << sz(path) << '\n';
        for (const int v : path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
}
