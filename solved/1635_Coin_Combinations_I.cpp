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

    int n, S;
    while (cin >> n >> S) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> dp(S + 1);
        dp[0] = 1;
        for (int s = 0; s < S; s++) {
            for (const int val : a) {
                if (s + val <= S) {
                    dp[s + val] += dp[s];
                    if (dp[s + val] >= MOD) {
                        dp[s + val] -= MOD;
                    }
                }
            }
        }

        cout << dp[S] << '\n';
    }
}
