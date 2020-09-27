#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

// maximum speed
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
const char* dir = "RDLU";

const int n = 7;

// these 3 variables are not const
// maximum speed
char s[n * n];
bool used[n][n];
int ans;

inline bool inRange(const int x, const int y) {
    return (0 <= x && x < n) && (0 <= y && y < n);
}

inline bool isFree(const int x, const int y) {
    return inRange(x, y) && !used[x][y];
}

inline void rec(const int x, const int y, const int pos) {
    const int dist = (n - 1 - x) + y;
    if (pos + dist > n * n - 1) {
        return;
    }
    if (pos == n * n - 1) {
        assert(x == n - 1);
        assert(y == 0);
        ans++;
        return;
    }
    if (dist == 0) {
        return;
    }
    for (int z = 0; z < 4; z++) {
        if (s[pos] != '?') {
            if (s[pos] != dir[z]) {
                continue;
            }
        }
        const int nx = x + dx[z];
        const int ny = y + dy[z];
        if (!isFree(nx, ny)) {
            continue;
        }
        // forward, right, left
        const int fnx = nx + dx[z];
        const int fny = ny + dy[z];
        const int rnx = nx + dx[(z + 1) & 3];
        const int rny = ny + dy[(z + 1) & 3];
        const int lnx = nx + dx[(z + 3) & 3];
        const int lny = ny + dy[(z + 3) & 3];
        const bool freeF = isFree(fnx, fny);
        if (!freeF) {
            const bool freeL = isFree(lnx, lny);
            const bool freeR = isFree(rnx, rny);
            if (freeL && freeR) {
                continue;
            }
        }
        used[nx][ny] = true;
        rec(nx, ny, pos + 1);
        used[nx][ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    while (cin >> s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                used[i][j] = false;
            }
        }
        used[0][0] = true;
        ans = 0;

        auto t1 = chrono::high_resolution_clock::now();
        rec(0, 0, 0);
        auto t2 = chrono::high_resolution_clock::now();
        auto totalTime = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
        cerr << "Total time for input " << s << ": " << totalTime << " ms" << endl;

        cout << ans << endl;
    }
}
