#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const vector<int> dx = {0, 1, 0, -1};
const vector<int> dy = {1, 0, -1, 0};

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

        auto inRange = [&](const int x, const int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        auto isGood = [&](const int x, const int y) {
            return inRange(x, y) && a[x][y] != '#';
        };

        vector<vector<bool>> vis(n, vector<bool>(m));
        int ans = 0;
        function<void(int,int)> dfs = [&](const int x, const int y) {
            assert(!vis[x][y]);
            vis[x][y] = true;
            for (int z = 0; z < 4; z++) {
                const int nx = x + dx[z];
                const int ny = y + dy[z];
                if (isGood(nx, ny) && !vis[nx][ny]) {
                    dfs(nx, ny);
                }
            }
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] != '#' && !vis[i][j]) {
                    ans++;
                    dfs(i, j);
                }
            }
        }
        cout << ans << '\n';
    }
}
