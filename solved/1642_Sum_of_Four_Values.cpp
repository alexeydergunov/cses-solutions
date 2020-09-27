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
    ll S;
    while (cin >> n >> S) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<pair<ll, ii>> pairs;
        pairs.reserve(n * (n - 1) / 2);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pairs.emplace_back(a[i] + a[j], ii(i, j));
            }
        }
        sort(all(pairs));

        auto haveSameIndices = [](const ii& z1, const ii& z2) {
            if (z1.first == z2.first) return true;
            if (z1.first == z2.second) return true;
            if (z1.second == z2.first) return true;
            if (z1.second == z2.second) return true;
            return false;
        };

        bool found = false;
        int j = sz(pairs) - 1;
        for (int i = 0; i < sz(pairs); i++) {
            const ll toFind = S - pairs[i].first;
            while (j >= 0 && pairs[j].first > toFind) {
                j--;
            }
            while (j >= 0 && pairs[j].first == toFind && haveSameIndices(pairs[i].second, pairs[j].second)) {
                j--;
            }
            if (j >= 0 && pairs[j].first == toFind) {
                found = true;
                auto [i1, i2] = pairs[i].second;
                auto [i3, i4] = pairs[j].second;
                cout << i1 + 1 << ' ' << i2 + 1 << ' ' << i3 + 1 << ' ' << i4 + 1 << '\n';
                break;
            }
        }

        if (!found) {
            cout << "IMPOSSIBLE" << '\n';
        }
    }
}
