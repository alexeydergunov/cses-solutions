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
        const ll sum = (ll)n * (n + 1) / 2;
        if (sum % 2 != 0) {
            cout << "NO" << '\n';
            continue;
        }

        vector<int> a;
        int now = n;
        ll sumA = 0;
        while (true) {
            if (sumA + now < sum / 2) {
                a.push_back(now);
                sumA += now;
                now--;
            } else {
                a.push_back(int(sum / 2 - sumA));
                break;
            }
        }
        sort(all(a));

        vector<int> b;
        for (int x = 1; x <= n; x++) {
            if (!binary_search(all(a), x)) {
                b.push_back(x);
            }
        }

        assert(accumulate(all(a), 0LL) == sum / 2);
        assert(accumulate(all(b), 0LL) == sum / 2);

        cout << "YES" << '\n';
        cout << sz(a) << '\n';
        for (int x : a) cout << x << ' ';
        cout << '\n';
        cout << sz(b) << '\n';
        for (int x : b) cout << x << ' ';
        cout << '\n';
    }
}
