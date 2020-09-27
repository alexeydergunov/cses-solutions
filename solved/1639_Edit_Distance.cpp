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

    string s, t;
    while (cin >> s >> t) {
        const int n = sz(s);
        const int m = sz(t);
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));
        dp[0][0] = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i + 1 <= n) {
                    // delete i-th from s
                    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
                }
                if (j + 1 <= m) {
                    // delete j-th from t
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
                }
                if (i + 1 <= n && j + 1 <= m) {
                    if (s[i] == t[j]) {
                        // they match
                        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
                    } else {
                        // replace
                        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
                    }
                }
            }
        }
        cout << dp[n][m] << '\n';
    }
}
