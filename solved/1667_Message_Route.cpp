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

        vector<int> dist(n, INF);
        vector<int> parent(n, -1);
        queue<int> q;
        q.push(0);
        dist[0] = 0;
        while (!q.empty()) {
            const int x = q.front(); q.pop();
            for (const int y : g[x]) {
                if (dist[y] > dist[x] + 1) {
                    dist[y] = dist[x] + 1;
                    parent[y] = x;
                    q.push(y);
                }
            }
        }

        if (dist[n - 1] >= INF) {
            cout << "IMPOSSIBLE" << '\n';
        } else {
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
}
