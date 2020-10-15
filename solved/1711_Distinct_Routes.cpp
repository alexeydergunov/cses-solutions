#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct Edge {
    int x, y;
    ll cap, flow;
};

struct MaxFlow {
    int source, sink;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> ptr;
    vector<ll> dist;

    MaxFlow(int n) {
        g.resize(n);
        ptr.resize(n);
        dist.resize(n);
    }

    void addEdge(int x, int y, ll cap) {
        g[x].push_back(sz(edges));
        edges.push_back(Edge{x, y, cap, 0});
        g[y].push_back(sz(edges));
        edges.push_back(Edge{y, x, 0, 0});
    }

    bool bfs() {
        fill(all(dist), INF);
        dist[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            const int x = q.front(); q.pop();
            for (const int edgeId : g[x]) {
                const Edge& e = edges[edgeId];
                if (e.flow < e.cap) {
                    if (dist[e.y] > dist[x] + 1) {
                        dist[e.y] = dist[x] + 1;
                        q.push(e.y);
                    }
                }
            }
        }
        return dist[sink] < INF;
    }

    ll dfs(const int x, const ll toPush) {
        if (x == sink) return toPush;
        if (toPush == 0) return 0;
        for (; ptr[x] < sz(g[x]); ptr[x]++) {
            const int edgeId = g[x][ptr[x]];
            Edge& e = edges[edgeId];
            if (dist[e.y] == dist[x] + 1) {
                const ll pushed = dfs(e.y, min(toPush, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    edges[edgeId ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll getMaxFlow() {
        ll result = 0;
        while (true) {
            if (!bfs()) {
                break;
            }
            fill(all(ptr), 0);
            while (true) {
                const ll pushed = dfs(source, INF);
                if (pushed > 0) {
                    result += pushed;
                } else {
                    break;
                }
            }
        }
        return result;
    }

    vector<vector<int>> getPaths() {
        const int n = sz(g);
        const int m = sz(edges);
        vector<vector<int>> paths;
        vector<bool> usedEdge(m);
        while (true) {
            queue<int> q;
            q.push(source);
            vector<bool> vis(n);
            vis[source] = true;
            vector<int> parentEdge(n, -1);
            while (!q.empty()) {
                const int x = q.front(); q.pop();
                for (const int edgeId : g[x]) {
                    if (usedEdge[edgeId]) continue;
                    const Edge& e = edges[edgeId];
                    if (e.cap == 0) continue;
                    if (e.cap != e.flow) continue;
                    if (!vis[e.y]) {
                        vis[e.y] = true;
                        parentEdge[e.y] = edgeId;
                        q.push(e.y);
                    }
                }
            }
            if (!vis[sink]) {
                break;
            }
            vector<int> path;
            int now = sink;
            while (true) {
                path.push_back(now);
                if (now == source) break;
                const int edgeId = parentEdge[now];
                now = edges[edgeId].x;
                usedEdge[edgeId] = true;
            }
            reverse(all(path));
            paths.push_back(path);
        }
        return paths;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        MaxFlow mf(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            mf.addEdge(x, y, 1);
        }
        mf.source = 0;
        mf.sink = n - 1;

        const ll flow = mf.getMaxFlow();
        const vector<vector<int>>& paths = mf.getPaths();
        assert(flow == sz(paths));

        cout << flow << '\n';
        for (const vector<int>& path : paths) {
            cout << sz(path) << '\n';
            for (const int x : path) {
                cout << x + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
