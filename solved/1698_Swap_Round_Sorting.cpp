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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }

        // because we need to output indices, not values
        vector<int> rev(n);
        for (int i = 0; i < n; i++) {
            rev[a[i]] = i;
        }
        a = rev;

        vector<vector<int>> cycles;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (vis[a[i]]) {
                continue;
            }
            vector<int> cycle;
            int x = a[i];
            while (true) {
                vis[x] = true;
                cycle.push_back(x);
                x = a[x];
                if (vis[x]) {
                    assert(x == a[i]);
                    break;
                }
            }
            if (sz(cycle) > 1) {
                cycles.push_back(cycle);
            }
        }

        vector<vector<ii>> ans(2);
        for (vector<int>& cycle : cycles) {
            assert(sz(cycle) >= 2);
            for (int L = 0, R = sz(cycle) - 1; L < R; L++, R--) {
                ans[0].emplace_back(cycle[L], cycle[R]);
                swap(cycle[L], cycle[R]);
            }
            for (int L = 1, R = sz(cycle) - 1; L < R; L++, R--) {
                ans[1].emplace_back(cycle[L], cycle[R]);
                swap(cycle[L], cycle[R]);
            }
        }
        while (!ans.empty() && ans.back().empty()) {
            ans.pop_back();
        }

        cout << sz(ans) << '\n';
        for (const vector<ii>& ansRound : ans) {
            cout << sz(ansRound) << '\n';
            for (const auto [x, y] : ansRound) {
                cout << x + 1 << ' ' << y + 1 << '\n';
            }
        }
    }
}
