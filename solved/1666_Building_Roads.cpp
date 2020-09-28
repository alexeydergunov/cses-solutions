#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

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

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        p[x] = y;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        DSU dsu(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            dsu.merge(x, y);
        }

        vector<ii> ans;
        for (int i = 1; i < n; i++) {
            if (dsu.find(i) != dsu.find(0)) {
                ans.emplace_back(0, i);
                dsu.merge(0, i);
            }
        }

        cout << sz(ans) << '\n';
        for (const auto [x, y] : ans) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
