#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m, Q;
    while (cin >> n >> m >> Q) {
        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) {
            d[i][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int x, y;
            ll cost;
            cin >> x >> y >> cost;
            x--; y--;
            d[x][y] = min(d[x][y], cost);
            d[y][x] = min(d[y][x], cost);
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }

        while (Q--) {
            int x, y;
            cin >> x >> y;
            x--; y--;

            ll ans = d[x][y];
            if (ans >= INF) {
                ans = -1;
            }
            cout << ans << '\n';
        }
    }
}
