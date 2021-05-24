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

    int T;
    cin >> T;
    while (T--) {
        ll k;
        cin >> k;
        k--;

        int len = 1;
        ll cnt = 9;
        ll pow10 = 1;
        while (k >= cnt * len) {
            k -= cnt * len;
            cnt *= 10;
            pow10 *= 10;
            len++;
        }
        // now take the k-th digit among all numbers with length == len

        int dig = int(k % len);
        ll num = pow10 + k / len;
        for (int i = 0; i < len - 1 - dig; i++) {
            num /= 10;
        }
        cout << num % 10 << '\n';
    }
}
