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
    vector<int> q; // queue

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
        q.clear();
        q.push_back(source);
        for (int qi = 0; qi < sz(q); qi++) { // as while (!q.empty()) but don't pop anything
            const int x = q[qi];
            for (const int edgeId : g[x]) {
                const Edge& e = edges[edgeId];
                if (e.flow < e.cap) {
                    if (dist[e.y] > dist[x] + 1) {
                        dist[e.y] = dist[x] + 1;
                        q.push_back(e.y);
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

    vector<ii> getMinCut() {
        vector<ii> result;
        // queue contains all reachable vertices
        for (const int x : q) {
            assert(dist[x] < INF);
            for (const int edgeId : g[x]) {
                const Edge& e = edges[edgeId];
                if (e.cap == 0) {
                    continue;
                }
                if (dist[e.y] == INF) {
                    result.emplace_back(x, e.y);
                }
            }
        }
        return result;
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
            mf.addEdge(y, x, 1);
        }
        mf.source = 0;
        mf.sink = n - 1;

        const ll flow = mf.getMaxFlow();
        const vector<ii>& ans = mf.getMinCut();
        assert(flow == sz(ans));

        cout << sz(ans) << '\n';
        for (const auto [x, y] : ans) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
