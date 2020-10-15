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

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n);
        vector<int> inDeg(n);
        vector<int> outDeg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
            inDeg[y]++;
            outDeg[x]++;
        }

        bool failByDeg = false;
        for (int i = 1; i < n - 1; i++) {
            if (inDeg[i] != outDeg[i]) {
                failByDeg = true;
                break;
            }
        }
        if (outDeg[0] - inDeg[0] != 1) {
            failByDeg = true;
        }
        if (inDeg[n - 1] - outDeg[n - 1] != 1) {
            failByDeg = true;
        }
        if (failByDeg) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        vector<int> ans;
        vector<int> ptr(n);
        vector<int> st = {0};
        while (!st.empty()) {
            const int x = st.back();
            if (ptr[x] == sz(g[x])) {
                // nowhere to go
                ans.push_back(x);
                st.pop_back();
            } else {
                const int y = g[x][ptr[x]++];
                st.push_back(y);
            }
        }

        bool allEdgesVisited = true;
        for (int x = 0; x < n; x++) {
            if (ptr[x] != sz(g[x])) {
                allEdgesVisited = false;
                break;
            }
        }
        if (!allEdgesVisited) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        assert(sz(ans) == m + 1);
        reverse(all(ans));
        assert(ans[0] == 0);
        assert(ans.back() == n - 1);
        for (int x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}
