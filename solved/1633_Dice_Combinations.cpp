#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<ll> dp(n + 1);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= i + 6 && j <= n; j++) {
                dp[j] += dp[i];
                dp[j] %= MOD;
            }
        }
        cout << dp[n] << '\n';
    }
}
