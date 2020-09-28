#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

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

        vector<int> parent(n, -1);
        vector<int> color(n);
        int start = -1;
        int finish = -1;
        function<void(int,int)> dfs = [&](const int x, const int p) {
            color[x] = 1;
            parent[x] = p;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                if (color[y] == 1) {
                    // found cycle
                    start = x;
                    finish = y;
                    return;
                }
                if (color[y] == 0) {
                    dfs(y, x);
                    if (start != -1) {
                        return;
                    }
                }
            }
            color[x] = 2;
        };

        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                if (start == -1) {
                    dfs(i, -1);
                }
            }
        }

        if (start == -1) {
            cout << "IMPOSSIBLE" << '\n';
        } else {
            vector<int> cycle;
            int x = start;
            while (true) {
                cycle.push_back(x);
                if (x == finish) break;
                x = parent[x];
            }
            cycle.push_back(start);

            cout << sz(cycle) << '\n';
            for (const int v : cycle) {
                cout << v + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
