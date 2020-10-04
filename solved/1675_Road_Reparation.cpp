#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Edge {
    int x, y;
    ll cost;
};

struct DSU {
    vector<int> p;

    DSU(int n) {
        p.resize(n);
        iota(all(p), 0);
    }

    int find(const int x) {
        if (x == p[x]) return x;
        return p[x] = find(p[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        p[x] = y;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<Edge> edges(m);
        for (Edge& e : edges) {
            cin >> e.x >> e.y >> e.cost;
            e.x--; e.y--;
        }
        sort(all(edges), [](const Edge& e1, const Edge& e2) {
            return e1.cost < e2.cost;
        });

        DSU dsu(n);
        ll ans = 0;
        int cnt = n;
        for (const Edge& e : edges) {
            if (dsu.merge(e.x, e.y)) {
                ans += e.cost;
                cnt--;
            }
        }

        if (cnt == 1) {
            cout << ans << '\n';
        } else {
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}
