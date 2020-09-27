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

    int n, S;
    while (cin >> n >> S) {
        vector<ii> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(all(a));

        bool found = false;
        for (const auto& e1 : a) {
            auto it = lower_bound(all(a), ii(S - e1.first, -1));
            // skip the same element
            while (it != a.end() && it->second == e1.second) {
                it++;
            }
            if (it == a.end()) {
                continue;
            }
            const auto& e2 = *it;
            assert(e1.first + e2.first >= S);
            if (e1.first + e2.first == S) {
                found = true;
                cout << e1.second + 1 << ' ' << e2.second + 1 << '\n';
                break;
            }
        }
        if (!found) {
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}
