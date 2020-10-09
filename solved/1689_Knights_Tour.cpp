#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const vector<int> dx = {2, 2, 1, -1, -2, -2, -1, 1};
const vector<int> dy = {-1, 1, 2, 2, 1, -1, -2, -2};

bool inRange(const int x, const int y) {
    return (0 <= x && x < 8) && (0 <= y && y < 8);
}

vector<vector<int>> solve(const int sx, const int sy) {
    vector<vector<int>> deg(8, vector<int>(8));
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int cnt = 0;
            for (int z = 0; z < 8; z++) {
                const int nx = x + dx[z];
                const int ny = y + dy[z];
                if (inRange(nx, ny)) {
                    cnt++;
                }
            }
            deg[x][y] = cnt;
        }
    }

    auto updateDeg = [&](const int x, const int y, const int delta) {
        assert(abs(delta) == 1);
        for (int z = 0; z < 8; z++) {
            const int nx = x + dx[z];
            const int ny = y + dy[z];
            if (inRange(nx, ny)) {
                deg[nx][ny] += delta;
            }
        }
    };

    vector<vector<int>> a(8, vector<int>(8));
    bool found = false;
    function<void(int,int,int)> rec = [&](const int x, const int y, const int step) {
        assert(a[x][y] == step);
        if (step == 64) {
            found = true;
            return;
        }

        vector<pair<ii, int>> next;
        for (int z = 0; z < 8; z++) {
            const int nx = x + dx[z];
            const int ny = y + dy[z];
            if (inRange(nx, ny) && a[nx][ny] == 0) {
                if (deg[nx][ny] > 0 || (step == 63 && deg[nx][ny] == 0)) {
                    next.emplace_back(ii(nx, ny), deg[nx][ny]);
                }
            }
        }
        sort(all(next), [](const auto& p1, const auto& p2) {
            return p1.second < p2.second;
        });

        for (const auto& p : next) {
            const auto [nx, ny] = p.first;
            a[nx][ny] = step + 1;
            updateDeg(nx, ny, -1);
            rec(nx, ny, step + 1);
            if (found) {
                return;
            }
            a[nx][ny] = 0;
            updateDeg(nx, ny, 1);
        }
    };

    a[sx][sy] = 1;
    updateDeg(sx, sy, -1);
    rec(sx, sy, 1);
    assert(found);
    return a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int sx, sy;
    cin >> sx >> sy;
    sx--; sy--;
    swap(sx, sy); // they give (col, row)

    const vector<vector<int>>& a = solve(sx, sy);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}
