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

    int n, k;
    while (cin >> n >> k) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        auto getCnt = [&](const ll maxS) {
            int cnt = 0;
            for (int i = 0; i < n; ) {
                int j = i;
                ll curS = 0;
                while (j < n && curS + a[j] <= maxS) {
                    curS += a[j];
                    j++;
                }
                cnt++;
                i = j;
            }
            return cnt;
        };

        ll left = *max_element(all(a));
        ll right = accumulate(all(a), 0LL);
        ll ans = -1;
        while (left <= right) {
            ll mid = (left + right) / 2;
            if (getCnt(mid) <= k) { // getCnt(mid) < k is fine too: we can split any subarray and answer won't decrease
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
