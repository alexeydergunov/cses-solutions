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

    int n, Q;
    while (cin >> n >> Q) {
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            g[p].push_back(i);
        }

        const int logN = int(log2(n + 1e-9)) + 1;
        vector<vector<int>> parent(logN, vector<int>(n));
        vector<int> h(n);
        function<void(int,int,int)> dfs = [&](const int x, const int p, const int curH) {
            parent[0][x] = p;
            h[x] = curH;
            for (const int y : g[x]) {
                dfs(y, x, curH + 1);
            }
        };
        dfs(0, 0, 0);

        for (int lvl = 1; lvl < logN; lvl++) {
            for (int x = 0; x < n; x++) {
                parent[lvl][x] = parent[lvl - 1][parent[lvl - 1][x]];
            }
        }

        auto up = [&](int x, const int d) {
            for (int lvl = logN - 1; lvl >= 0; lvl--) {
                if (d & (1 << lvl)) {
                    x = parent[lvl][x];
                }
            }
            return x;
        };

        while (Q--) {
            int x, d;
            cin >> x >> d;
            x--;
            if (h[x] < d) {
                cout << -1;
            } else {
                cout << up(x, d) + 1;
            }
            cout << '\n';
        }
    }
}
