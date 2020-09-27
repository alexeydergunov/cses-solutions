#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(2e9) + 1; // larger than any element

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> dp(n + 1, INF);
        dp[0] = a[0];
        for (int i = 1; i < n; i++) {
            *lower_bound(all(dp), a[i]) = a[i];
        }

        int ans = int(lower_bound(all(dp), INF) - dp.begin());
        cout << ans << '\n';
    }
}
