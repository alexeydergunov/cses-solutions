#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(3e18); // higher than 1e9*1e9 + 1e9*1e9

vector<vector<ll>> mult(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    const int n = sz(a);
    assert(n == sz(a[0]));
    assert(n == sz(b));
    assert(n == sz(b[0]));
    vector<vector<ll>> res(n, vector<ll>(n, INF));
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]); // as in floyd
            }
        }
    }
    return res;
}

vector<vector<ll>> binpow(const vector<vector<ll>>& a, const ll p) {
    if (p == 0) {
        const int n = sz(a);
        assert(n == sz(a[0]));
        vector<vector<ll>> e(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) {
            e[i][i] = 0;
        }
        return e;
    }
    if (p % 2 == 0) {
        const vector<vector<ll>>& t = binpow(a, p / 2);
        return mult(t, t);
    }
    return mult(a, binpow(a, p - 1));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    ll k;
    while (cin >> n >> m >> k) {
        vector<vector<ll>> a(n, vector<ll>(n, INF));
        for (int i = 0; i < m; i++) {
            int x, y;
            ll w;
            cin >> x >> y >> w;
            x--; y--;
            a[x][y] = min(a[x][y], w);
        }

        const vector<vector<ll>>& res = binpow(a, k);
        ll ans = res[0][n - 1];
        if (ans >= INF) {
            ans = -1;
        }
        cout << ans << '\n';
    }
}
