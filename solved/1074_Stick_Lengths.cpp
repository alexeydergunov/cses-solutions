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

    int n;
    while (cin >> n) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(all(a));

        vector<ll> pref = a;
        for (int i = 1; i < n; i++) {
            pref[i] += pref[i - 1];
        }

        vector<ll> suff = a;
        for (int i = n - 2; i >= 0; i--) {
            suff[i] += suff[i + 1];
        }

        ll ans = ll(9e18);
        for (int i = 0; i < n; i++) {
            ll now = 0;
            if (i > 0) {
                const ll before = a[i] * i - pref[i - 1];
                now += before;
            }
            if (i < n - 1) {
                const ll after = suff[i + 1] - a[i] * (n - i - 1);
                now += after;
            }
            ans = min(ans, now);
        }
        cout << ans << '\n';
    }
}
