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

        ll best = ll(1e18);
        for (int mask = 0; mask < (1 << n); mask++) {
            ll sum1 = 0;
            ll sum2 = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    sum1 += a[i];
                } else {
                    sum2 += a[i];
                }
            }
            best = min(best, abs(sum1 - sum2));
        }
        cout << best << '\n';
    }
}
