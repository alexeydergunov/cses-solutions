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

    int n;
    while (cin >> n) {
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int start = 0;
        while (sz(g[start]) == 1) {
            start++;
        }
        assert(start < n);

        vector<int> leaves;
        function<void(int,int)> dfs = [&](const int x, const int p) {
            if (sz(g[x]) == 1) {
                leaves.push_back(x);
            }
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x);
            }
        };
        dfs(start, -1);
        assert(sz(leaves) >= 2);

        vector<ii> ans;
        for (int i = 0; i < sz(leaves) / 2; i++) {
            ans.emplace_back(leaves[i], leaves[i + sz(leaves) / 2]);
        }
        if (sz(leaves) % 2 != 0) {
            ans.emplace_back(leaves[0], leaves.back());
        }

        cout << sz(ans) << '\n';
        for (const auto [x, y] : ans) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
