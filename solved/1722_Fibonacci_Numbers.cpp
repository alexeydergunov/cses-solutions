#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;

vector<vector<ll>> mult(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    vector<vector<ll>> res(2, vector<ll>(2));
    for (int i = 0; i < 2; i++) {
        for (int k = 0; k < 2; k++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}

vector<vector<ll>> binpow(const vector<vector<ll>>& a, const ll p) {
    if (p == 0) {
        return {{1, 0}, {0, 1}};
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
        // | 1 1 |   | F[i-1] |    |  F[i]  |
        // |     | * |        | == |        |
        // | 1 0 |   | F[i-2] |    | F[i-1] |
        vector<vector<ll>> a = {{1, 1}, {1, 0}};
        a = binpow(a, n);
        cout << a[0][1] << '\n';
    }
}
