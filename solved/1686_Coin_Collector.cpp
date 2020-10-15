#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

ll getMaxPath(const vector<vector<int>>& g, const vector<ll>& cost) {
    const int n = sz(g);
    vector<int> inDeg(n);
    for (int x = 0; x < n; x++) {
        for (const int y : g[x]) {
            inDeg[y]++;
        }
    }
    queue<int> q;
    vector<ll> dp(n, -INF);
    for (int i = 0; i < n; i++) {
        if (inDeg[i] == 0) {
            q.push(i);
            dp[i] = cost[i];
        }
    }
    while (!q.empty()) {
        const int x = q.front(); q.pop();
        for (const int y : g[x]) {
            dp[y] = max(dp[y], dp[x] + cost[y]);
            inDeg[y]--;
            if (inDeg[y] == 0) {
                q.push(y);
            }
        }
    }
    return *max_element(all(dp));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<ll> cost(n);
        for (int i = 0; i < n; i++) {
            cin >> cost[i];
        }
        vector<vector<int>> g(n);
        vector<vector<int>> rg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            rg[y].push_back(x);
        }

        // strongly connected components, part 1 (topsort)
        vector<int> order;
        vector<bool> vis(n);
        function<void(int)> dfs = [&](const int x) {
            assert(!vis[x]);
            vis[x] = true;
            for (const int y : g[x]) {
                if (!vis[y]) {
                    dfs(y);
                }
            }
            order.push_back(x);
        };
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        reverse(all(order));

        // strongly connected components, part 2 (dfs on reversed graph)
        vector<int> compId(n, -1);
        int compCnt = 0;
        function<void(int)> dfs2 = [&](const int x) {
            assert(compId[x] == -1);
            compId[x] = compCnt;
            for (const int y : rg[x]) {
                if (compId[y] == -1) {
                    dfs2(y);
                }
            }
        };
        for (const int x : order) {
            if (compId[x] == -1) {
                dfs2(x);
                compCnt++;
            }
        }

        // build component graph
        vector<vector<int>> compGraph(compCnt);
        vector<ll> compCost(compCnt);
        for (int x = 0; x < n; x++) {
            const int cx = compId[x];
            compCost[cx] += cost[x];
            for (const int y : g[x]) {
                const int cy = compId[y];
                if (cx != cy) {
                    compGraph[cx].push_back(cy);
                }
            }
        }

        const ll ans = getMaxPath(compGraph, compCost);
        cout << ans << '\n';
    }
}
