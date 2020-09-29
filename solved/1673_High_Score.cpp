#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct Edge {
    int from, to;
    ll cost;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        for (Edge& e : edges) {
            cin >> e.from >> e.to >> e.cost;
            e.from--; e.to--;
        }

        vector<ll> dist(n, -INF);
        vector<int> parent(n, -1);
        dist[0] = 0;

        auto run = [&]() {
            for (const Edge& e : edges) {
                if (dist[e.to] < dist[e.from] + e.cost) {
                    dist[e.to] = dist[e.from] + e.cost;
                    parent[e.to] = e.from;
                }
            }
        };

        for (int i = 0; i < n - 1; i++) {
            run();
        }

        const vector<ll> before = dist;
        run();
        const vector<ll> after = dist;

        // vertices whose distances are changed, lie on infinite cycles
        // find infinite cycles using parent array
        // after this bfs, isOnCycle[x] = true if x lies on an infinite cycle
        queue<int> qc;
        vector<bool> isOnCycle(n);
        for (int i = 0; i < n; i++) {
            if (before[i] != after[i]) {
                isOnCycle[i] = true;
                qc.push(i);
            }
        }
        while (!qc.empty()) {
            const int x = qc.front(); qc.pop();
            const int p = parent[x];
            if (p != -1 && !isOnCycle[p]) {
                isOnCycle[p] = true;
                qc.push(p);
            }
        }

        // check which cycles are reachable from 0 by forward edges, and from (n - 1) by back edges
        auto getCycleReachability = [&](const int start, const vector<vector<int>>& g) {
            vector<bool> vis(n);
            queue<int> q;
            q.push(start);
            vis[start] = true;
            while (!q.empty()) {
                const int x = q.front(); q.pop();
                for (const int y : g[x]) {
                    if (!vis[y]) {
                        vis[y] = true;
                        q.push(y);
                    }
                }
            }
            vector<bool> res(n);
            for (int i = 0; i < n; i++) {
                if (vis[i] && isOnCycle[i]) {
                    res[i] = true;
                }
            }
            return res;
        };

        vector<vector<int>> g(n);
        vector<vector<int>> rg(n);
        for (const Edge& e : edges) {
            g[e.from].push_back(e.to);
            rg[e.to].push_back(e.from);
        }
        const vector<bool> startReachability = getCycleReachability(0, g);
        const vector<bool> finishReachability = getCycleReachability(n - 1, rg);
        bool infinite = false;
        for (int i = 0; i < n; i++) {
            if (startReachability[i] && finishReachability[i]) {
                infinite = true;
            }
        }

        cout << (infinite ? -1 : dist[n - 1]) << '\n';
    }
}
