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

    int n, Q;
    while (cin >> n >> Q) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<ll> pref = a;
        for (int i = 1; i < n; i++) {
            pref[i] ^= pref[i - 1];
        }

        auto get = [&](int L, int R) {
            ll res = pref[R];
            if (L > 0) res ^= pref[L - 1];
            return res;
        };

        while (Q--) {
            int L, R;
            cin >> L >> R;
            L--; R--;
            cout << get(L, R) << '\n';
        }
    }
}
