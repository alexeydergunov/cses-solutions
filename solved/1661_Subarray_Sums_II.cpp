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
    ll S;
    while (cin >> n >> S) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        map<ll, int> mp;
        mp[0] = 1;
        ll ans = 0;
        ll pref = 0;
        for (int i = 0; i < n; i++) {
            pref += a[i];
            auto it = mp.find(pref - S);
            if (it != mp.end()) {
                ans += it->second;
            }
            mp[pref]++;
        }
        cout << ans << '\n';
    }
}
