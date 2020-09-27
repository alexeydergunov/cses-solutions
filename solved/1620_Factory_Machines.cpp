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
    ll needCnt;
    while (cin >> n >> needCnt) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        auto can = [&](const ll t) {
            ll cnt = 0;
            for (int i = 0; i < n; i++) {
                cnt += t / a[i];
                if (cnt >= needCnt) break;
            }
            return cnt >= needCnt;
        };

        ll left = 0;
        ll right = ll(1e18);
        ll ans = -1;
        while (left <= right) {
            ll mid = (left + right) / 2;
            if (can(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        assert(ans != -1);
        cout << ans << '\n';
    }
}
