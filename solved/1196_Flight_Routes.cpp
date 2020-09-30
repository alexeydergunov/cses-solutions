#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Edge {
    int to;
    ll cost;
};

struct Vertex {
    int id;
    ll dist;

    bool operator < (const Vertex& v) const {
        if (dist != v.dist) return dist < v.dist;
        return id < v.id;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<vector<Edge>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            ll cost;
            cin >> x >> y >> cost;
            x--; y--;
            g[x].push_back(Edge{y, cost});
        }

        vector<vector<ll>> dist(n);
        for (int i = 0; i < n; i++) {
            dist[i].reserve(k + 1);
        }
        dist[0].push_back(0);
        multiset<Vertex> s;
        s.insert({0, 0});
        while (!s.empty()) {
            const auto [x, d] = *s.begin();
            s.erase(s.begin());
            for (const auto [y, cost] : g[x]) {
                assert(sz(dist[y]) <= k);
                const auto it = upper_bound(all(dist[y]), d + cost);
                if (it == dist[y].end() && sz(dist[y]) == k) {
                    continue;
                }
                dist[y].insert(it, d + cost);
                s.insert(Vertex{y, d + cost});
                if (sz(dist[y]) > k) {
                    s.erase(s.find(Vertex{y, dist[y].back()}));
                    dist[y].pop_back();
                }
            }
        }
        assert(sz(dist[n - 1]) == k); // guaranteed

        for (const ll d : dist[n - 1]) {
            cout << d << ' ';
        }
        cout << '\n';
    }
}
