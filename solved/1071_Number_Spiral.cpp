#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

ll f(const ll r, const ll c) {
    const ll layer = max(r, c);

    const ll last = layer * layer;
    const ll first = (layer - 1) * (layer - 1) + 1;
    assert(last % 2 == first % 2);

    const ll center = (last + first) / 2;

    if (layer % 2 == 0) {
        if (layer == r) {
            return center + (layer - c);
        } else {
            return center - (layer - r);
        }
    } else {
        if (layer == r) {
            return center - (layer - c);
        } else {
            return center + (layer - r);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int T;
    cin >> T;
    while (T--) {
        ll r, c;
        cin >> r >> c;

        ll ans = f(r, c);
        cout << ans << '\n';
    }
}
