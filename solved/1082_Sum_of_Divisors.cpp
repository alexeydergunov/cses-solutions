#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;
const ll INV2 = (MOD + 1) / 2;

ll getConsecutiveSum(const ll first, const ll last) {
    assert(first <= last);
    const ll len = (last - first + 1) % MOD;
    return (first + last) % MOD * len % MOD * INV2 % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    ll n;
    while (cin >> n) {
        const ll sqrtN = ll(sqrt(double(n) + 1e-9));

        ll ans = 0;
        ll cur = n;
        for (int cnt = 1; cnt < sqrtN; cnt++) {
            const ll next = n / (cnt + 1);
            // all numbers in range [next + 1 ... cur] have cnt divisors
            ans += getConsecutiveSum(next + 1, cur) * cnt;
            ans %= MOD;
            cur = next;
        }
        for (int x = 1; x <= cur; x++) {
            const ll cnt = n / x;
            ans += cnt * x;
            ans %= MOD;
        }

        cout << ans << '\n';
    }
}
