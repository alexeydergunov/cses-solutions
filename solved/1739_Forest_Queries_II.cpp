#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct FenwickTree {
    int n;
    vector<vector<int>> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1, vector<int>(n + 1));
    }

    void inc(int x, int y, const int delta) {
        // 1-indexed
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= n; j += j & -j) {
                t[i][j] += delta;
            }
        }
    }

    int get(int x, int y) {
        // 1-indexed
        int res = 0;
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                res += t[i][j];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<string> field(n);
        for (int i = 0; i < n; i++) {
            cin >> field[i];
        }

        FenwickTree t(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (field[i][j] == '*') {
                    t.inc(i, j, 1);
                }
            }
        }

        while (Q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int x, y;
                cin >> x >> y;
                x--; y--;
                if (field[x][y] == '*') {
                    field[x][y] = '.';
                    t.inc(x, y, -1);
                } else {
                    field[x][y] = '*';
                    t.inc(x, y, 1);
                }
            } else {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                x1--; y1--; x2--; y2--;
                int ans = t.get(x2, y2);
                ans -= t.get(x1 - 1, y2);
                ans -= t.get(x2, y1 - 1);
                ans += t.get(x1 - 1, y1 - 1);
                cout << ans << '\n';
            }
        }
    }
}
