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
            g[y].push_back(x);
        }

        vector<int> color(n, -1);
        bool fail = false;
        function<void(int,int,int)> dfs = [&](const int x, const int p, const int curC) {
            assert(color[x] == -1);
            color[x] = curC;
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                if (color[y] == curC) {
                    fail = true;
                    return;
                }
                if (color[y] == -1) {
                    dfs(y, x, 1 - curC);
                    if (fail) {
                        return;
                    }
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                dfs(i, -1, 0);
            }
        }

        if (fail) {
            cout << "IMPOSSIBLE" << '\n';
        } else {
            for (const int c : color) {
                cout << c + 1 << ' ';
            }
            cout << '\n';
        }
    }
}
