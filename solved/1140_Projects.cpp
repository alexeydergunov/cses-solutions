#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Project {
    int L, R, cost;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<Project> projects(n);
        for (auto& p : projects) {
            cin >> p.L >> p.R >> p.cost;
            p.R++; // [L, R)
        }

        vector<int> coords;
        coords.reserve(2 * n);
        for (const auto& p : projects) {
            coords.push_back(p.L);
            coords.push_back(p.R);
        }
        sort(all(coords));
        coords.resize(unique(all(coords)) - coords.begin());

        auto getCoord = [&](const int x) {
            auto it = lower_bound(all(coords), x);
            assert(it != coords.end());
            assert(*it == x);
            return int(it - coords.begin());
        };

        for (auto& p : projects) {
            p.L = getCoord(p.L);
            p.R = getCoord(p.R);
        }
        sort(all(projects), [](const Project& p1, const Project& p2) {
            return p1.L < p2.L;
        });

        vector<ll> dp(sz(coords) + 1);
        int ptr = 0;
        for (int x = 0; x < sz(coords); x++) {
            dp[x + 1] = max(dp[x + 1], dp[x]);
            while (ptr < n && projects[ptr].L < x) {
                ptr++;
            }
            while (ptr < n && projects[ptr].L == x) {
                const Project& p = projects[ptr];
                dp[p.R] = max(dp[p.R], dp[p.L] + p.cost);
                ptr++;
            }
        }
        assert(ptr == n);

        cout << dp.back() << '\n';
    }
}
