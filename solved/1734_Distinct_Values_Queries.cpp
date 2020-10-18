#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SegmentTree {
    int n;
    vector<vector<int>> t;

    SegmentTree(const vector<int>& a) {
        n = sz(a);
        t.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<int>& a) {
        t[v].reserve(r - l + 1);
        if (l == r) {
            t[v].push_back(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        merge(all(t[2 * v]), all(t[2 * v + 1]), back_inserter(t[v]));
    }

    int getLowerBound(int v, int l, int r, int needL, int needR, const int x) {
        if (l == needL && r == needR) {
            return int(lower_bound(all(t[v]), x) - t[v].begin());
        }
        int m = (l + r) / 2;
        if (needR <= m) {
            return getLowerBound(2 * v, l, m, needL, needR, x);
        }
        if (m + 1 <= needL) {
            return getLowerBound(2 * v + 1, m + 1, r, needL, needR, x);
        }
        int res1 = getLowerBound(2 * v, l, m, needL, m, x);
        int res2 = getLowerBound(2 * v + 1, m + 1, r, m + 1, needR, x);
        return res1 + res2;
    }

    int getLowerBound(int needL, int needR, const int x) {
        return getLowerBound(1, 0, n - 1, needL, needR, x);
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

        map<int, int> lastPos;
        vector<int> nextPos(n, n);
        for (int i = 0; i < n; i++) {
            const auto it = lastPos.find(a[i]);
            if (it != lastPos.end()) {
                nextPos[it->second] = i;
            }
            lastPos[a[i]] = i;
        }
        // number of distinct values among a[L]...a[R] is equal to
        // number of values > R among nextPos[L]...nextPos[R]

        SegmentTree t(nextPos);
        while (Q--) {
            int L, R;
            cin >> L >> R;
            L--; R--;
            const int len = R - L + 1;
            const int lowerBoundIndex = t.getLowerBound(L, R, R + 1);
            cout << len - lowerBoundIndex << '\n';
        }
    }
}
