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
        vector<vector<int>> rg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            rg[y].push_back(x);
        }

        // topsort on forward edges
        vector<bool> vis(n);
        vector<int> order;
        function<void(int)> dfs = [&](const int x) {
            vis[x] = true;
            for (const int y : g[x]) {
                if (!vis[y]) dfs(y);
            }
            order.push_back(x);
        };
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfs(i);
        }
        assert(sz(order) == n);
        reverse(all(order));

        // iterate in topsort order, by back edges, find components
        vector<int> comp(n, -1);
        int compCnt = 0;
        function<void(int)> dfs2 = [&](const int x) {
            comp[x] = compCnt;
            for (const int y : rg[x]) {
                if (comp[y] == -1) dfs2(y);
            }
        };
        for (const int i : order) {
            if (comp[i] == -1) {
                dfs2(i);
                compCnt++;
            }
        }

        if (compCnt == 1) {
            cout << "YES" << '\n';
        } else {
            assert(compCnt >= 2);
            int v0 = -1;
            int v1 = -1;
            for (int i = 0; i < n; i++) {
                if (comp[i] == 0) v0 = i;
                if (comp[i] == 1) v1 = i;
            }
            assert(v0 != -1);
            assert(v1 != -1);
            cout << "NO" << '\n';
            cout << v1 + 1 << ' ' << v0 + 1 << '\n';
        }
    }
}
