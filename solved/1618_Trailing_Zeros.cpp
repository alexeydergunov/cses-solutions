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

    ll n;
    while (cin >> n) {
        ll twos = 0;
        for (ll p = 2; p <= n; p *= 2) {
            twos += n / p;
        }

        ll fives = 0;
        for (ll p = 5; p <= n; p *= 5) {
            fives += n / p;
        }

        cout << min(twos, fives) << '\n';
    }
}
