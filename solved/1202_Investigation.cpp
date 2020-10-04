#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;
const int INF32 = int(1e9);
const ll INF64 = ll(1e18);

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

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

        vector<ll> dist(n, INF64);
        vector<int> cnt(n);
        vector<int> shortest(n, INF32);
        vector<int> longest(n, -INF32);
        priority_queue<Vertex> pq;
        pq.push(Vertex{0, 0});
        dist[0] = 0;
        cnt[0] = 1;
        shortest[0] = 0;
        longest[0] = 0;
        while (!pq.empty()) {
            const auto [x, d] = pq.top(); pq.pop();
            if (d != dist[x]) {
                continue;
            }
            for (const auto [y, cost] : g[x]) {
                if (dist[y] > dist[x] + cost) {
                    dist[y] = dist[x] + cost;
                    cnt[y] = cnt[x];
                    shortest[y] = shortest[x] + 1;
                    longest[y] = longest[x] + 1;
                    pq.push(Vertex{y, dist[y]});
                } else if (dist[y] == dist[x] + cost) {
                    add(cnt[y], cnt[x]);
                    shortest[y] = min(shortest[y], shortest[x] + 1);
                    longest[y] = max(longest[y], longest[x] + 1);
                }
            }
        }

        cout << dist[n - 1] << ' ' << cnt[n - 1] << ' ' << shortest[n - 1] << ' ' << longest[n - 1] << '\n';
    }
}
