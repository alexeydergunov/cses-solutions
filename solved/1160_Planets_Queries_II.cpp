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

    int n, Q;
    while (cin >> n >> Q) {
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }

        vector<int> cycleId(n, -1);
        vector<int> posInCycle(n, -1);
        vector<vector<int>> cycles(n);
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
                    posInCycle[y] = j - pos;
                    cycles[x].push_back(y);
                }
            }
        }

        const int logN = int(log2(n + 1e-9)) + 1;
        queue<int> q;
        vector<int> distToCycle(n, -1);
        vector<vector<int>> parent(logN, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            for (const int x : cycles[i]) {
                distToCycle[x] = 0;
                parent[0][x] = x;
                q.push(x);
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
                    parent[0][y] = x;
                    q.push(y);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            assert(cycleId[i] != -1);
            assert(distToCycle[i] != -1);
        }
        for (int z = 1; z < logN; z++) {
            for (int x = 0; x < n; x++) {
                parent[z][x] = parent[z - 1][parent[z - 1][x]];
            }
        }

        auto up = [&](int x, int d) {
            assert(0 <= d && d < (1 << logN));
            for (int z = logN - 1; z >= 0; z--) {
                if (d & (1 << z)) {
                    x = parent[z][x];
                }
            }
            return x;
        };

        auto getAns = [&](int start, int finish) {
            if (cycleId[start] != cycleId[finish]) {
                return -1;
            }
            const int c = cycleId[start];
            if (distToCycle[start] == 0) {
                if (distToCycle[finish] == 0) {
                    const int pos1 = posInCycle[start];
                    const int pos2 = posInCycle[finish];
                    return (pos2 - pos1 + sz(cycles[c])) % sz(cycles[c]);
                } else {
                    return -1;
                }
            } else {
                if (distToCycle[finish] == 0) {
                    const int pos1 = posInCycle[up(start, distToCycle[start])];
                    const int pos2 = posInCycle[finish];
                    return distToCycle[start] + (pos2 - pos1 + sz(cycles[c])) % sz(cycles[c]);
                } else {
                    if (distToCycle[start] < distToCycle[finish]) {
                        return -1;
                    }
                    const int d = distToCycle[start] - distToCycle[finish];
                    if (up(start, d) != finish) {
                        return -1;
                    }
                    return d;
                }
            }
        };

        while (Q--) {
            int start, finish;
            cin >> start >> finish;
            start--; finish--;
            cout << getAns(start, finish) << '\n';
        }
    }
}
