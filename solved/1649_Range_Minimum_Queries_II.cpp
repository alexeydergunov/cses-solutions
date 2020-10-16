#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(const vector<int>& a) {
        n = sz(a);
        t.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        combine(v);
    }

    void combine(int v) {
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    void setValue(int v, int l, int r, int pos, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) {
            setValue(2 * v, l, m, pos, val);
        } else {
            setValue(2 * v + 1, m + 1, r, pos, val);
        }
        combine(v);
    }

    void setValue(int pos, int val) {
        setValue(1, 0, n - 1, pos, val);
    }

    int getMin(int v, int l, int r, int needL, int needR) {
        if (l == needL && r == needR) {
            return t[v];
        }
        int m = (l + r) / 2;
        if (needR <= m) {
            return getMin(2 * v, l, m, needL, needR);
        }
        if (m + 1 <= needL) {
            return getMin(2 * v + 1, m + 1, r, needL, needR);
        }
        int res1 = getMin(2 * v, l, m, needL, m);
        int res2 = getMin(2 * v + 1, m + 1, r, m + 1, needR);
        return min(res1, res2);
    }

    int getMin(int needL, int needR) {
        return getMin(1, 0, n - 1, needL, needR);
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

        SegmentTree t(a);
        while (Q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int pos, value;
                cin >> pos >> value;
                pos--;
                t.setValue(pos, value);
            } else {
                int L, R;
                cin >> L >> R;
                L--; R--;
                cout << t.getMin(L, R) << '\n';
            }
        }
    }
}
