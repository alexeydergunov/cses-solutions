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

        vector<int> order;
        vector<int> start(n), finish(n);
        function<void(int,int)> dfs = [&](const int x, const int p) {
            start[x] = sz(order);
            order.push_back(x);
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x);
            }
            finish[x] = sz(order) - 1; // both ends included
        };
        dfs(0, -1);
        assert(sz(order) == n);
        for (int i = 0; i < n; i++) {
            assert(start[i] <= finish[i]);
        }

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
                const int dfsLeftIndex = start[x];
                const int dfsRightIndex = finish[x];
                cout << t.sum(dfsRightIndex) - t.sum(dfsLeftIndex - 1) << '\n';
            }
        }
    }
}
