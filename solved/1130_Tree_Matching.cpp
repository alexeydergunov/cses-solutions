#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        // 0 - not chosen
        // 1 - chosen, lower
        // 2 - chosen, higher
        vector<vector<int>> dp(n, vector<int>(3, -INF));
        function<void(int,int)> dfs = [&](int x, int p) {
            dp[x][0] = 0;
            dp[x][1] = 0;
            dp[x][2] = 0;
            int maxChooseHigherDiff = -INF;
            for (int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x);
                const int childNotLower = max(dp[y][0], dp[y][2]);
                maxChooseHigherDiff = max(maxChooseHigherDiff, dp[y][1] - childNotLower);
                dp[x][0] += childNotLower;
                dp[x][1] += childNotLower;
                dp[x][2] += childNotLower;
            }
            dp[x][2] += maxChooseHigherDiff;
            dp[x][2]++;
        };
        dfs(0, -1);

        cout << max(dp[0][0], dp[0][2]) << '\n';
    }
}
