#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, -1, 0, 1};

vector<vector<ld>> mult(const vector<vector<ld>>& a, const vector<vector<ld>>& b) {
    const int n = sz(a);
    assert(n == sz(a[0]));
    assert(n == sz(b));
    assert(n == sz(b[0]));
    vector<vector<ld>> res(n, vector<ld>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

vector<vector<ld>> binpow(const vector<vector<ld>>& a, const ll p) {
    if (p == 0) {
        const int n = sz(a);
        assert(n == sz(a[0]));
        vector<vector<ld>> e(n, vector<ld>(n));
        for (int i = 0; i < n; i++) {
            e[i][i] = 1.0;
        }
        return e;
    }
    if (p % 2 == 0) {
        const vector<vector<ld>>& t = binpow(a, p / 2);
        return mult(t, t);
    }
    return mult(a, binpow(a, p - 1));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(6); cout.setf(ios::fixed); // they require exactly 6 decimal places
    cerr.precision(15); cerr.setf(ios::fixed);

    int k;
    while (cin >> k) {
        auto inRange = [](const int x, const int y) {
            return 0 <= x && x < 8 && 0 <= y && y < 8;
        };
        auto getId = [](int x, int y) {
            return x * 8 + y;
        };

        vector<vector<ld>> a(64, vector<ld>(64));
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                const int idFrom = getId(x, y);
                vector<ii> moves;
                for (int z = 0; z < 4; z++) {
                    const int nx = x + dx[z];
                    const int ny = y + dy[z];
                    if (inRange(nx, ny)) {
                        moves.emplace_back(nx, ny);
                    }
                }
                const ld moveProb = 1.0 / sz(moves);
                for (const auto [nx, ny] : moves) {
                    const int idTo = getId(nx, ny);
                    a[idFrom][idTo] += moveProb;
                }
            }
        }
        a = binpow(a, k);

        ld ans = 0.0;        
        for (int idTo = 0; idTo < 64; idTo++) {
            ld cellAns = 1.0;
            for (int idFrom = 0; idFrom < 64; idFrom++) {
                cellAns *= (1.0 - a[idFrom][idTo]);
            }
            ans += cellAns;
        }
        cout << ans << '\n';
    }
}
