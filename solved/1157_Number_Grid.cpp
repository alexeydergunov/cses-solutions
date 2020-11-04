#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

ll f(ll x, ll y, const ll side) {
    if (side == 0) {
        return 0;
    }
    assert((side & (side - 1)) == 0); // side is a power of 2
    ll result = 0;
    if (x >= side) {
        result ^= side;
        x -= side;
    }
    if (y >= side) {
        result ^= side;
        y -= side;
    }
    return result | f(x, y, side / 2);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    ll x, y;
    while (cin >> x >> y) {
        x--; y--;
        cout << f(x, y, 1LL << 30) << '\n';
    }
}
