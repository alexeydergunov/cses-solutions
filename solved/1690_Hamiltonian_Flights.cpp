#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

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

        vector<vector<int>> dp(1 << n, vector<int>(n)); // mask, last
        dp[1][0] = 1;
        for (int mask = 0; mask < (1 << n); mask++) {
            for (int last = 0; last < n; last++) {
                const int curVal = dp[mask][last];
                if (curVal == 0) {
                    continue;
                }
                for (int next : g[last]) {
                    if (mask & (1 << next)) {
                        continue;
                    }
                    add(dp[mask | (1 << next)][next], curVal);
                }
            }
        }

        cout << dp[(1 << n) - 1][n - 1] << '\n';
    }
}
