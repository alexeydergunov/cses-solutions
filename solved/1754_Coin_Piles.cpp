#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

bool f(ll a, ll b) {
    if ((a + b) % 3 != 0) {
        return false;
    }

    if (a > b) {
        swap(a, b);
    }
    // now a <= b

    return 2 * a >= b;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int T;
    cin >> T;
    while (T--) {
        ll a, b;
        cin >> a >> b;
        cout << (f(a, b) ? "YES" : "NO") << '\n';
    }
}
