#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

const vector<int> dx = {0, 1, 0, -1};
const vector<int> dy = {1, 0, -1, 0};
const string dir = "RDLU";

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int sx = -1, sy = -1;
        int fx = -1, fy = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == 'A') {
                    sx = i;
                    sy = j;
                }
                if (a[i][j] == 'B') {
                    fx = i;
                    fy = j;
                }
            }
        }
        assert(sx != -1);
        assert(fx != -1);

        auto inRange = [&](const int x, const int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        auto isGood = [&](const int x, const int y) {
            return inRange(x, y) && a[x][y] != '#';
        };

        vector<vector<int>> dist(n, vector<int>(m, INF));
        vector<vector<ii>> parentCell(n, vector<ii>(m, {-1, -1}));
        vector<vector<char>> parentDir(n, vector<char>(m));
        queue<ii> q;
        q.emplace(sx, sy);
        dist[sx][sy] = 0;
        while (!q.empty()) {
            const auto [x, y] = q.front(); q.pop();
            for (int z = 0; z < 4; z++) {
                const int nx = x + dx[z];
                const int ny = y + dy[z];
                if (isGood(nx, ny)) {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        parentCell[nx][ny] = {x, y};
                        parentDir[nx][ny] = dir[z];
                        q.emplace(nx, ny);
                    }
                }
            }
        }

        if (dist[fx][fy] >= INF) {
            cout << "NO" << '\n';
        } else {
            string path;
            int x = fx;
            int y = fy;
            while (true) {
                if (x == sx && y == sy) break;
                const char c = parentDir[x][y];
                assert(c != 0);
                path += c;
                const auto [px, py] = parentCell[x][y];
                x = px;
                y = py;
            }
            reverse(all(path));
            cout << "YES" << '\n';
            cout << sz(path) << '\n';
            cout << path << '\n';
        }
    }
}
