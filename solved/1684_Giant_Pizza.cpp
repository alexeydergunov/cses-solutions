#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

vector<int> getComponentIds(const vector<vector<int>>& g) {
    const int n = sz(g);
    vector<vector<int>> rg(n);
    for (int x = 0; x < n; x++) {
        for (const int y : g[x]) {
            rg[y].push_back(x);
        }
    }

    // strongly connected components, part 1 (topsort)
    vector<int> order;
    vector<bool> vis(n);
    function<void(int)> dfs = [&](const int x) {
        assert(!vis[x]);
        vis[x] = true;
        for (const int y : g[x]) {
            if (!vis[y]) {
                dfs(y);
            }
        }
        order.push_back(x);
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    reverse(all(order));

    // strongly connected components, part 2 (dfs on reversed graph)
    vector<int> compId(n, -1);
    int compCnt = 0;
    function<void(int)> dfs2 = [&](const int x) {
        assert(compId[x] == -1);
        compId[x] = compCnt;
        for (const int y : rg[x]) {
            if (compId[y] == -1) {
                dfs2(y);
            }
        }
    };
    for (const int x : order) {
        if (compId[x] == -1) {
            dfs2(x);
            compCnt++;
        }
    }

    // validate components ordering
    for (int x = 0; x < n; x++) {
        for (const int y : g[x]) {
            // for each edge (x, y), compId[x] <= compId[y]
            assert(compId[x] <= compId[y]);
        }
    }
    return compId;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int clauseCnt, n;
    while (cin >> clauseCnt >> n) {
        // 0, 2, 4, ..., (2n - 2) - positive
        // 1, 3, 5, ..., (2n - 1) - negative
        vector<vector<int>> g(2 * n);
        while (clauseCnt--) {
            char cx, cy;
            int x, y;
            cin >> cx >> x >> cy >> y;
            x--; y--;
            // for (x || y) add edges (!x -> y) and (!y -> x)
            x *= 2;
            y *= 2;
            if (cx == '-') x++;
            if (cy == '-') y++;
            g[x ^ 1].push_back(y);
            g[y ^ 1].push_back(x);
        }

        const vector<int>& compId = getComponentIds(g);

        bool fail = false;
        for (int x = 0; x < 2 * n; x += 2) {
            if (compId[x] == compId[x ^ 1]) {
                fail = true;
                break;
            }
        }
        if (fail) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        string ans;
        for (int x = 0; x < 2 * n; x += 2) {
            if (compId[x] > compId[x ^ 1]) {
                ans += '+';
            } else {
                ans += '-';
            }
        }
        for (const char c : ans) {
            cout << c << ' ';
        }
        cout << '\n';
    }
}
