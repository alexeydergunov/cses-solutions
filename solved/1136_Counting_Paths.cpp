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
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<ii> paths(m);
        for (auto& z : paths) {
            cin >> z.first >> z.second;
            z.first--;
            z.second--;
        }

        const int logN = int(log2(n + 1e-9)) + 1;
        vector<vector<int>> parent(logN, vector<int>(n));
        vector<int> h(n);
        function<void(int,int,int)> dfs = [&](const int x, const int p, const int curH) {
            parent[0][x] = p;
            h[x] = curH;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x, curH + 1);
            }
        };
        dfs(0, 0, 0);

        for (int lvl = 1; lvl < logN; lvl++) {
            for (int x = 0; x < n; x++) {
                parent[lvl][x] = parent[lvl - 1][parent[lvl - 1][x]];
            }
        }

        auto up = [&](int x, const int d) {
            for (int lvl = logN - 1; lvl >= 0; lvl--) {
                if (d & (1 << lvl)) {
                    x = parent[lvl][x];
                }
            }
            return x;
        };

        auto getLCA = [&](int x, int y) {
            if (h[x] < h[y]) {
                swap(x, y);
            }
            // now h[x] >= h[y]
            x = up(x, h[x] - h[y]);
            assert(h[x] == h[y]);
            if (x == y) {
                return x;
            }
            for (int lvl = logN - 1; lvl >= 0; lvl--) {
                if (parent[lvl][x] != parent[lvl][y]) {
                    x = parent[lvl][x];
                    y = parent[lvl][y];
                }
            }
            assert(parent[0][x] == parent[0][y]);
            return parent[0][x];
        };

        vector<int> pathStarts(n);
        vector<int> pathEnds(n);
        for (const auto [x, y] : paths) {
            const int lca = getLCA(x, y);
            pathStarts[x]++;
            pathStarts[y]++;
            pathEnds[lca] += 2;
        }

        vector<int> ans(n);
        function<int(int,int)> dfs2 = [&](const int x, const int p) {
            int curPaths = 0;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                const int childPaths = dfs2(y, x);
                curPaths += childPaths;
            }
            curPaths += pathStarts[x];
            assert(pathEnds[x] % 2 == 0); // because two ends meets here in lca
            curPaths -= pathEnds[x] / 2;
            ans[x] = curPaths;
            curPaths -= pathEnds[x] / 2;
            return curPaths;
        };
        const int pathsHigherFromRoot = dfs2(0, -1);
        assert(pathsHigherFromRoot == 0);

        for (const int val : ans) {
            cout << val << ' ';
        }
        cout << '\n';
    }
}
