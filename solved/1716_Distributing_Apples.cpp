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

ll inv(ll x) {
    return binpow(x, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    const int maxN = 2000000;
    vector<ll> fact(maxN + 1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    vector<ll> invFact(maxN + 1);
    invFact[maxN] = inv(fact[maxN]);
    for (int i = maxN - 1; i >= 0; i--) {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
    assert(invFact[0] == 1);

    int n, m;
    while (cin >> n >> m) {
        // m balls, insert (n-1) walls between them
        ll up = fact[m + n - 1];
        ll invDown = invFact[m] * invFact[n - 1] % MOD;
        cout << up * invDown % MOD << '\n';
    }
}
