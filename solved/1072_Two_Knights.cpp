#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

ll f(const int n) {
    const ll total = (ll)n * n * ((ll)n * n - 1) / 2;
    if (n <= 5) {
        int bad = 0;
        for (int x1 = 0; x1 < n; x1++) {
            for (int y1 = 0; y1 < n; y1++) {
                for (int x2 = 0; x2 < n; x2++) {
                    for (int y2 = 0; y2 < n; y2++) {
                        if (x1 == y1 && x2 == y2) {
                            continue;
                        }
                        vector<int> d = {abs(x1 - x2), abs(y1 - y2)};
                        sort(all(d));
                        if (d[0] == 1 && d[1] == 2) {
                            bad++;
                        }
                    }
                }
            }
        }
        return total - bad / 2;
    } else {
        ll bad = 0;
        bad += 4 * 2; // a1
        bad += 8 * 3; // a2
        bad += 4 * 4; // b2
        bad += 4 * (n - 4) * 4; // a3, a4, ...
        bad += 4 * (n - 4) * 6; // b3, b4, ...
        bad += (n - 4) * (n - 4) * 8; // center
        return total - bad / 2;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    cin >> n;
    for (int k = 1; k <= n; k++) {
        cout << f(k) << '\n';
    }
}
