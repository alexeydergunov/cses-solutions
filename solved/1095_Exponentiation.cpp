#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;

ll binpow(ll x, ll p) {
    if (p == 0) return 1;
    if (p % 2 == 0) {
        ll t = binpow(x, p / 2);
        return t * t % MOD;
    }
    return x * binpow(x, p - 1) % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int T;
    cin >> T;
    while (T--) {
        ll a, b;
        cin >> a >> b;
        cout << binpow(a, b) << '\n';
    }
}
