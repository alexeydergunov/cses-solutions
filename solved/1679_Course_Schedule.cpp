#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
        }

        vector<int> order;
        vector<int> color(n);
        bool fail = false;
        function<void(int)> dfs = [&](const int x) {
            assert(color[x] == 0);
            color[x] = 1;
            for (const int y : g[x]) {
                if (color[y] == 1) {
                    fail = true;
                    return;
                }
                if (color[y] == 0) {
                    dfs(y);
                    if (fail) return;
                }
            }
            color[x] = 2;
            order.push_back(x);
        };

        for (int i = 0; i < n; i++) {
            if (color[i] == 0) {
                dfs(i);
            }
        }

        if (fail) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }
        assert(sz(order) == n);
        reverse(all(order));

        for (const int x : order) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}
