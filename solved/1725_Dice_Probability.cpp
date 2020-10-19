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

    int n, L, R;
    while (cin >> n >> L >> R) {
        vector<ld> dp(6 * n + 1);
        dp[0] = 1.0;
        for (int i = 0; i < n; i++) {
            vector<ld> newDp(6 * n + 1);
            for (int s = 0; s <= 6 * i; s++) {
                for (int newS = s + 1; newS <= s + 6; newS++) {
                    newDp[newS] += dp[s] / 6.0;
                }
            }
            dp.swap(newDp);
        }

        ld ans = 0.0;
        for (int s = L; s <= R; s++) {
            ans += dp[s];
        }
        cout << ans << '\n';
    }
}
