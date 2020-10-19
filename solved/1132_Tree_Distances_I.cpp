#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

vector<int> getDistances(const vector<vector<int>>& g, const int start) {
    const int n = sz(g);
    vector<int> dist(n);
    function<void(int,int,int)> dfs = [&](int x, int p, int curDist) {
        dist[x] = curDist;
        for (int y : g[x]) {
            if (y == p) {
                continue;
            }
            dfs(y, x, curDist + 1);
        }
    };
    dfs(start, -1, 0);
    return dist;
}

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
        const vector<int>& dist0 = getDistances(g, 0);

        const int diamEnd1 = int(max_element(all(dist0)) - dist0.begin());
        const vector<int>& dist1 = getDistances(g, diamEnd1);

        const int diamEnd2 = int(max_element(all(dist1)) - dist1.begin());
        const vector<int>& dist2 = getDistances(g, diamEnd2);

        for (int i = 0; i < n; i++) {
            cout << max(dist1[i], dist2[i]) << ' ';
        }
        cout << '\n';
    }
}
