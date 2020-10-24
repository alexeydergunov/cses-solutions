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
    ll needS;
    while (cin >> n >> needS) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        const int n1 = n / 2;
        const int n2 = n - n1;
        vector<ll> v1, v2;
        v1.reserve(1 << n1);
        v2.reserve(1 << n2);
        for (int mask = 0; mask < (1 << n1); mask++) {
            ll sum = 0;
            for (int i = 0; i < n1; i++) {
                if (mask & (1 << i)) {
                    sum += a[i];
                }
            }
            v1.push_back(sum);
        }
        for (int mask = 0; mask < (1 << n2); mask++) {
            ll sum = 0;
            for (int i = 0; i < n2; i++) {
                if (mask & (1 << i)) {
                    sum += a[n1 + i];
                }
            }
            v2.push_back(sum);
        }
        sort(all(v1));
        sort(all(v2));

        ll ans = 0;
        int R2 = sz(v2) - 1;
        for (int L1 = 0; L1 < sz(v1); ) {
            int R1 = L1;
            while (R1 < sz(v1) && v1[L1] == v1[R1]) {
                R1++;
            }
            const int len1 = R1 - L1;

            while (R2 >= 0 && v1[L1] + v2[R2] > needS) {
                R2--;
            }
            int L2 = R2;
            while (L2 >= 0 && v1[L1] + v2[L2] == needS) {
                L2--;
            }
            const int len2 = R2 - L2;

            ans += ll(len1) * len2;
            R2 = L2;
            L1 = R1;
        }

        cout << ans << '\n';
    }
}
