#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    ll n;
    while (cin >> n) {
        n++;
        ll ans = 0;
        for (ll pw = 1; pw <= n; pw *= 2) {
            // main: (00..0011..11)*
            ans += n / (2 * pw) * pw;
            // last 00..0011..11
            ll rem = n % (2 * pw);
            ans += max(0LL, rem - pw);
        }
        cout << ans << '\n';
    }
}
