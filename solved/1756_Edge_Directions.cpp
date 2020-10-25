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
        vector<ii> edges;
        edges.reserve(m);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
            edges.emplace_back(x, y);
        }

        vector<int> order;
        vector<bool> vis(n);
        function<void(int,int)> dfs = [&](const int x, const int p) {
            assert(!vis[x]);
            vis[x] = true;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                if (!vis[y]) {
                    dfs(y, x);
                }
            }
            order.push_back(x);
        };
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1);
            }
        }
        reverse(all(order));
        assert(sz(order) == n);

        vector<int> revOrder(n);
        for (int i = 0; i < n; i++) {
            revOrder[order[i]] = i;
        }

        for (auto [x, y] : edges) {
            if (revOrder[x] < revOrder[y]) {
                 swap(x, y);
            }
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
