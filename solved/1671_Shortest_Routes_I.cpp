#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct Edge {
    int to;
    ll cost;
};

struct Vertex {
    int id;
    ll dist;

    bool operator < (const Vertex& v) const {
        return dist > v.dist;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<Edge>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            ll cost;
            cin >> x >> y >> cost;
            x--; y--;
            g[x].push_back(Edge{y, cost});
        }

        vector<ll> dist(n, INF);
        priority_queue<Vertex> pq;
        pq.push(Vertex{0, 0});
        dist[0] = 0;
        while (!pq.empty()) {
            const auto [x, d] = pq.top(); pq.pop();
            if (d != dist[x]) {
                continue;
            }
            for (const auto [y, cost] : g[x]) {
                if (dist[y] > dist[x] + cost) {
                    dist[y] = dist[x] + cost;
                    pq.push(Vertex{y, dist[y]});
                }
            }
        }

        for (const ll d : dist) {
            cout << d << ' ';
        }
        cout << '\n';
    }
}
