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
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        vector<int> s(n);
        vector<int> d(n);
        function<void(int,int,int)> dfs = [&](int x, int p, int curDist) {
            s[x] = 1;
            d[x] = curDist;
            for (int y : g[x]) {
                if (y == p) {
                    continue;
                }
                dfs(y, x, curDist + 1);
                s[x] += s[y];
            }
        };
        dfs(0, -1, 0);

        vector<ll> ans(n);
        ll now = accumulate(all(d), 0LL);
        function<void(int,int)> dfs2 = [&](int x, int p) {
            ans[x] = now;
            for (int y : g[x]) {
                if (y == p) {
                    continue;
                }
                now -= s[y];
                now += n - s[y];
                dfs2(y, x);
                now -= n - s[y];
                now += s[y];
            }
        };
        dfs2(0, -1);

        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}
