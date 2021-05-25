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
        for (auto& x : a) {
            cin >> x;
        }
        sort(all(a));

        ll sum = 0;
        for (ll x : a) {
            if (x <= sum + 1) {
                sum += x;
            } else {
                break;
            }
        }
        cout << sum + 1 << '\n';
    }
}
