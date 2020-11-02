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

    int n, maxX;
    while (cin >> n >> maxX) {
        vector<int> w(n);
        for (int i = 0; i < n; i++) {
            cin >> w[i];
        }

        // dp[mask] == (min ans, min weight of the last ride)
        const int INF = maxX + 1;
        vector<ii> dp(1 << n, {n + 1, INF});
        dp[0] = {0, maxX}; // to force a new ride
        for (int mask = 0; mask < (1 << n); mask++) {
            const auto [curAns, curW] = dp[mask];
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    continue;
                }
                const int newMask = mask | (1 << i);
                // start a new ride
                if (curAns < n) {
                    dp[newMask] = min(dp[newMask], {curAns + 1, w[i]});
                }
                // extend existing ride
                if (curW + w[i] <= maxX) {
                    dp[newMask] = min(dp[newMask], {curAns, curW + w[i]});
                }
            }
        }

        cout << dp[(1 << n) - 1].first << '\n';
    }
}
