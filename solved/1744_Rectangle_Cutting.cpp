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

    int a, b;
    while (cin >> a >> b) {
        const int n = max(a, b);

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
        for (int i = 1; i <= n; i++) {
            dp[i][i] = 0;
        }

        function<int(int,int)> f = [&](int x, int y) {
            if (x > y) {
                swap(x, y);
            }
            // now x <= y

            if (dp[x][y] < INF) {
                return dp[x][y];
            }

            for (int z = 1; z <= x / 2; z++) {
                dp[x][y] = min(dp[x][y], f(z, y) + f(x - z, y) + 1);
            }
            for (int z = 1; z <= y / 2; z++) {
                dp[x][y] = min(dp[x][y], f(x, z) + f(x, y - z) + 1);
            }
            assert(dp[x][y] < INF);
            return dp[x][y];
        };
        cout << f(a, b) << '\n';
    }
}
