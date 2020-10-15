#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Edge {
    int to, id;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<Edge>> g(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            g[x].push_back(Edge{y, i});
            g[y].push_back(Edge{x, i});
        }

        bool hasOdd = false;
        for (int i = 0; i < n; i++) {
            if (sz(g[i]) % 2 != 0) {
                hasOdd = true;
                break;
            }
        }
        if (hasOdd) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        vector<int> ans;
        vector<bool> visEdge(m);
        vector<int> ptr(n);
        vector<int> st = {0};
        while (!st.empty()) {
            const int x = st.back();
            while (ptr[x] < sz(g[x]) && visEdge[g[x][ptr[x]].id]) {
                ptr[x]++;
            }
            if (ptr[x] == sz(g[x])) {
                // nowhere to go
                ans.push_back(x);
                st.pop_back();
            } else {
                const Edge& e = g[x][ptr[x]];
                st.push_back(e.to);
                visEdge[e.id] = true;
            }
        }

        bool allEdgesVisited = true;
        for (int i = 0; i < m; i++) {
            if (!visEdge[i]) {
                allEdgesVisited = false;
                break;
            }
        }
        if (!allEdgesVisited) {
            cout << "IMPOSSIBLE" << '\n';
            continue;
        }

        assert(sz(ans) == m + 1);
        for (int x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}
