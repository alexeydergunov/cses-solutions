#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        if (a[0][0] != '*') {
            dp[0][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == '*') {
                    continue;
                }
                if (i > 0) {
                    dp[i][j] += dp[i - 1][j];
                    if (dp[i][j] >= MOD) {
                        dp[i][j] -= MOD;
                    }
                }
                if (j > 0) {
                    dp[i][j] += dp[i][j - 1];
                    if (dp[i][j] >= MOD) {
                        dp[i][j] -= MOD;
                    }
                }
            }
        }
        cout << dp[n - 1][n - 1] << '\n';
    }
}
