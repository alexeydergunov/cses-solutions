#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;

vector<vector<ll>> mult(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    const int n = sz(a);
    assert(n == sz(a[0]));
    assert(n == sz(b));
    assert(n == sz(b[0]));
    vector<vector<ll>> res(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}

vector<vector<ll>> binpow(const vector<vector<ll>>& a, const ll p) {
    if (p == 0) {
        const int n = sz(a);
        assert(n == sz(a[0]));
        vector<vector<ll>> e(n, vector<ll>(n));
        for (int i = 0; i < n; i++) {
            e[i][i] = 1;
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

    ll n;
    while (cin >> n) {
        // F[i] == F[i-1] + ... + F[i-6]
        vector<vector<ll>> a(6, vector<ll>(6));
        for (int i = 0; i < 6; i++) {
            a[0][i] = 1;
        }
        for (int i = 1; i < 6; i++) {
            a[i][i - 1] = 1;
        }
        a = binpow(a, n + 1);
        cout << a[0][5] << '\n';
    }
}
