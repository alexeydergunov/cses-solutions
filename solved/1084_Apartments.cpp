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

    int n, m;
    ll k;
    while (cin >> n >> m >> k) {
        vector<ll> a(n), b(m);
        for (ll& x : a) cin >> x;
        for (ll& x : b) cin >> x;
        sort(all(a));
        sort(all(b));

        int ans = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j < m && b[j] < a[i] - k) {
                j++;
            }
            if (j < m && b[j] <= a[i] + k) {
                ans++;
                j++;
            }
        }
        cout << ans << '\n';
    }
}
