#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(6); cout.setf(ios::fixed); // they require exactly 6 decimal places
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, k;
    while (cin >> n >> k) {
        vector<ld> dp(k + 1);
        dp[0] = 1.0;
        for (int i = 0; i < n; i++) {
            vector<ld> newDp(k + 1);
            for (int oldMax = 0; oldMax <= k; oldMax++) {
                for (int newNum = 1; newNum <= k; newNum++) {
                    int newMax = max(oldMax, newNum);
                    newDp[newMax] += dp[oldMax] / k; // probability is (1 / k)
                }
            }
            dp.swap(newDp);
        }

        ld ans = 0.0;
        for (int mx = 1; mx <= k; mx++) {
            ans += mx * dp[mx];
        }
        cout << ans << '\n';
    }
}
