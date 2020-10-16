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
        vector<string> field(n);
        for (int i = 0; i < n; i++) {
            cin >> field[i];
        }

        // 1-indexed
        vector<vector<int>> pref(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (field[i - 1][j - 1] == '*') {
                    pref[i][j]++;
                }
                pref[i][j] += pref[i - 1][j];
                pref[i][j] += pref[i][j - 1];
                pref[i][j] -= pref[i - 1][j - 1];
            }
        }

        auto get = [&](int x1, int y1, int x2, int y2) {
            int res = pref[x2][y2];
            res -= pref[x1 - 1][y2];
            res -= pref[x2][y1 - 1];
            res += pref[x1 - 1][y1 - 1];
            return res;
        };

        while (Q--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << get(x1, y1, x2, y2) << '\n';
        }
    }
}
