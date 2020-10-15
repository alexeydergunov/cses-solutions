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

    int n1, n2, m;
    while (cin >> n1 >> n2 >> m) {
        const int n = n1 + n2;
        // [0..n1) - boys, [n1..n1+n2) - girls
        vector<vector<int>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            y += n1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> match(n, -1);
        vector<int> vis(n);
        int curMark = 0;
        function<bool(int)> dfs = [&](const int x) {
            if (vis[x] == curMark) return false;
            vis[x] = curMark;
            // first try all unmatched vertices
            for (const int y : g[x]) {
                if (match[y] == -1) {
                    match[x] = y;
                    match[y] = x;
                    return true;
                }
            }
            // then try to prolong chain
            for (const int y : g[x]) {
                if (match[y] != -1 && dfs(match[y])) {
                    match[x] = y;
                    match[y] = x;
                    return true;
                }
            }
            return false;
        };

        for (int i = 0; i < n1; i++) {
            curMark++; // vis.assign(n, false) in 1 operation
            dfs(i);
        }

        vector<ii> ans;
        for (int i = 0; i < n1; i++) {
            if (match[i] != -1) {
                ans.emplace_back(i, match[i]);
            }
        }

        cout << sz(ans) << '\n';
        for (const auto [x, y] : ans) {
            cout << x + 1 << ' ' << y - n1 + 1 << '\n';
        }
    }
}
