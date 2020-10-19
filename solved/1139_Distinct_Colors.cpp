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
        vector<int> color(n);
        for (int i = 0; i < n; i++) {
            cin >> color[i];
        }
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> ans(n);
        vector<set<int>> sets(n);
        function<void(int,int)> dfs = [&](const int x, const int p) {
            set<int>& result = sets[x];
            result.insert(color[x]);
            for (const int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x);
                set<int>& child = sets[y];
                if (sz(child) > sz(result)) {
                    result.swap(child); // small-to-large
                }
                assert(sz(result) >= sz(child));
                for (const int c : child) {
                    result.insert(c);
                }
            }
            ans[x] = sz(result);
        };
        dfs(0, -1);

        for (const int val : ans) {
            cout << val << ' ';
        }
        cout << '\n';
    }
}
