#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

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

        vector<ll> dist(n);
        vector<int> parent(n, -1);

        auto run = [&]() {
            for (const Edge& e : edges) {
                if (dist[e.to] > dist[e.from] + e.cost) {
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

        if (before == after) {
            cout << "NO" << '\n';
            continue;
        }

        int start = -1;
        for (int i = 0; i < n; i++) {
            if (before[i] != after[i]) {
                start = i;
            }
        }
        assert(start != -1);

        // go by parent links, find the vertex lying on the negative cycle
        vector<bool> vis(n);
        while (true) {
            if (vis[start]) break;
            vis[start] = true;
            start = parent[start];
        }

        // find the negative cycle itself
        vector<int> negCycle = {start};
        int x = start;
        while (true) {
            assert(parent[x] != -1);
            x = parent[x];
            negCycle.push_back(x);
            if (x == start) break;
        }
        reverse(all(negCycle));

        cout << "YES" << '\n';
        for (int v : negCycle) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
}
