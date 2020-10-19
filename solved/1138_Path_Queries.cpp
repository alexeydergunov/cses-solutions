#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct FenwickTree {
    int n;
    vector<ll> t;

    FenwickTree(const int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int i, const ll delta) {
        i++; // make 1-indexed
        while (i <= n) {
            t[i] += delta;
            i += i & -i;
        }
    }

    ll sum(int r) {
        r++; // make 1-indexed
        ll res = 0;
        while (r > 0) {
            res += t[r];
            r -= r & -r;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<ll> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> s(n);
        function<void(int,int)> dfs = [&](const int x, const int p) {
            s[x] = 1;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x);
                s[x] += s[y];
            }
        };
        dfs(0, -1);

        for (int x = 0; x < n; x++) {
            sort(all(g[x]), [&](const int v1, const int v2) {
                return s[v1] > s[v2];
            });
        }
        // now the first vertex in each adjacency list has the largest subtree size

        vector<int> parent(n, -1);
        vector<int> hh(n);
        vector<int> order;
        vector<int> start(n), finish(n);
        function<void(int,int,int)> dfs2 = [&](const int x, const int p, const int heavyHeight) {
            parent[x] = p;
            hh[x] = heavyHeight;
            start[x] = sz(order);
            order.push_back(x);
            int heavyChild = -1;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                if (heavyChild == -1) {
                    heavyChild = y;
                }
                const int newHeavyHeight = (y == heavyChild) ? heavyHeight + 1 : 0;
                dfs2(y, x, newHeavyHeight);
            }
            finish[x] = sz(order) - 1; // both ends included
        };
        dfs2(0, -1, 0);
        assert(sz(order) == n);

        FenwickTree t(n);
        for (int i = 0; i < n; i++) {
            const int dfsIndex = start[i];
            assert(order[dfsIndex] == i);
            t.inc(dfsIndex, v[i]);
        }

        while (Q--) {
            int type, x;
            cin >> type >> x;
            x--;
            if (type == 1) {
                ll value;
                cin >> value;
                const int dfsIndex = start[x];
                t.inc(dfsIndex, value - v[x]);
                v[x] = value;
            } else {
                ll ans = 0;
                int now = x;
                while (true) {
                    if (hh[now] > 0) {
                        // this is heavy vertex
                        // heavy path is a segment in dfs ordering
                        const int rightDfsIndex = start[now];
                        const int leftDfsIndex = rightDfsIndex - hh[now] + 1;
                        ans += t.sum(rightDfsIndex) - t.sum(leftDfsIndex - 1);
                        now = order[leftDfsIndex]; // go to the highest vertex in heavy path
                        now = parent[now];
                    } else {
                        ans += v[now];
                        now = parent[now];
                    }
                    if (now == -1) {
                        break;
                    }
                }
                cout << ans << '\n';
            }
        }
    }
}
