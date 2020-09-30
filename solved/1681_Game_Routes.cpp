#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n);
        vector<int> inDeg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            inDeg[y]++;
        }

        vector<int> dp(n);
        dp[0] = 1;
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDeg[i] == 0) {
                q.push(i); // even if we start from them, we will process vertex 0 eventually
            }
        }
        while (!q.empty()) {
            const int x = q.front(); q.pop();
            for (const int y : g[x]) {
                add(dp[y], dp[x]);
                inDeg[y]--;
                if (inDeg[y] == 0) {
                    q.push(y);
                }
            }
        }

        cout << dp[n - 1] << '\n';
    }
}
