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
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }

        vector<int> cycleId(n, -1);
        vector<int> cycleLen(n);
        vector<int> vis(n, -1);
        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) {
                int x = i;
                vector<int> path = {x};
                vis[x] = i;
                while (true) {
                    x = p[x];
                    if (vis[x] != -1) break;
                    path.push_back(x);
                    vis[x] = i;
                }
                if (vis[x] != i) { // reached other chain or cycle
                    continue;
                }
                assert(cycleId[x] == -1);
                // v1 -> v2 -> x -> v3 -> v4 -> x

                int pos = -1;
                for (int j = 0; j < sz(path); j++) {
                    if (path[j] == x) {
                        pos = j;
                        break;
                    }
                }
                assert(pos != -1);

                for (int j = pos; j < sz(path); j++) {
                    const int y = path[j];
                    cycleId[y] = x;
                    cycleLen[x]++;
                }
            }
        }

        queue<int> q;
        vector<int> distToCycle(n, -1);
        for (int i = 0; i < n; i++) {
            if (cycleId[i] != -1) {
                distToCycle[i] = 0;
                q.push(i);
            }
        }
        vector<vector<int>> rev(n);
        for (int i = 0; i < n; i++) {
            rev[p[i]].push_back(i);
        }
        while (!q.empty()) {
            const int x = q.front(); q.pop();
            for (const int y : rev[x]) {
                if (cycleId[y] == -1) {
                    assert(distToCycle[y] == -1);
                    distToCycle[y] = distToCycle[x] + 1;
                    cycleId[y] = cycleId[x];
                    q.push(y);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            assert(cycleId[i] != -1);
            assert(distToCycle[i] != -1);
        }

        for (int i = 0; i < n; i++) {
            const int c = cycleId[i];
            cout << distToCycle[i] + cycleLen[c] << ' ';
        }
        cout << '\n';
    }
}
