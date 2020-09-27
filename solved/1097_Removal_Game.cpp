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
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<vector<ll>> dp(n, vector<ll>(n));
        vector<vector<bool>> vis(n, vector<bool>(n));

        // returns score1 - score2
        function<ll(int,int)> f = [&](const int L, const int R) {
            if (L > R) {
                return 0LL;
            }
            if (vis[L][R]) {
                return dp[L][R];
            }
            vis[L][R] = true;
            if ((R - L + 1) % 2 == n % 2) {
                // first
                return dp[L][R] = max(f(L + 1, R) + a[L], f(L, R - 1) + a[R]);
            } else {
                // second
                return dp[L][R] = min(f(L + 1, R) - a[L], f(L, R - 1) - a[R]);
            }
        };

        const ll diff = f(0, n - 1);
        const ll sum = accumulate(all(a), 0LL);
        // score1 - score2 == diff
        // score1 + score2 == sum
        // score1 == (sum + diff) / 2
        assert((sum + diff) % 2 == 0);
        cout << (sum + diff) / 2 << '\n';
    }
}
