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
        vector<int> towers;

        auto add = [&](const int x) {
            const int i = int(upper_bound(all(towers), x) - towers.begin());
            if (i == sz(towers)) {
                towers.push_back(x);
            } else {
                towers[i] = x;
            }
        };

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            add(x);
        }
        cout << sz(towers) << '\n';
    }
}
