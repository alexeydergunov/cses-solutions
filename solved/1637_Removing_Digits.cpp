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
        vector<int> dp(n + 1, INF);
        dp[n] = 0;
        for (int x = n; x >= 1; x--) {
            int y = x;
            while (y > 0) {
                int d = y % 10;
                if (d != 0 && x - d >= 0) {
                    dp[x - d] = min(dp[x - d], dp[x] + 1);
                }
                y /= 10;
            }
        }
        cout << dp[0] << '\n';
    }
}
