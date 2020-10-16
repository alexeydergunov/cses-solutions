#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SparseTable {
    int n;
    int lvlCnt;
    vector<int> w;
    vector<int> len;
    vector<vector<int>> t;

    SparseTable(const vector<int>& a) {
        n = sz(a);

        // calculate length of each layer
        for (int segWidth = 1; 2 * segWidth <= n; segWidth *= 2) {
            w.push_back(segWidth);
            len.push_back(n - segWidth + 1);
        }
        lvlCnt = sz(len);

        // resize all layers
        t.resize(lvlCnt);
        for (int lvl = 0; lvl < lvlCnt; lvl++) {
            t[lvl].resize(len[lvl]);
        }

        // build table
        for (int i = 0; i < n; i++) {
            t[0][i] = a[i];
        }
        for (int lvl = 1; lvl < lvlCnt; lvl++) {
            for (int i = 0; i < len[lvl]; i++) {
                int j = i + w[lvl - 1];
                t[lvl][i] = min(t[lvl - 1][i], t[lvl - 1][j]);
            }
        }
    }

    int getMin(int l, int r) {
        assert(l <= r);
        const int width = r - l + 1;
        assert(width <= n);
        const int lvl = int(upper_bound(all(w), width) - w.begin()) - 1; // log(log(n))
        int res1 = t[lvl][l];
        int res2 = t[lvl][r - w[lvl] + 1];
        return min(res1, res2);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        SparseTable t(a);
        while (Q--) {
            int L, R;
            cin >> L >> R;
            L--; R--;
            cout << t.getMin(L, R) << '\n';
        }
    }
}
