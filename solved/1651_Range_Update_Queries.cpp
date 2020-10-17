#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SegmentTree {
    int n;
    vector<ll> t;
    vector<ll> add;
    vector<bool> isLeaf;

    SegmentTree(const vector<ll>& a) {
        n = sz(a);
        t.resize(4 * n + 1);
        add.resize(4 * n + 1);
        isLeaf.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            isLeaf[v] = true;
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
    }

    void push(int v) {
        t[v] += add[v];
        if (!isLeaf[v]) {
            add[2 * v] += add[v];
            add[2 * v + 1] += add[v];
        }
        add[v] = 0;
    }

    void inc(int v, int l, int r, int needL, int needR, ll delta) {
        if (l == needL && r == needR) {
            add[v] += delta;
            return;
        }
        push(v);
        int m = (l + r) / 2;
        if (needR <= m) {
            inc(2 * v, l, m, needL, needR, delta);
        } else if (m + 1 <= needL) {
            inc(2 * v + 1, m + 1, r, needL, needR, delta);
        } else {
            inc(2 * v, l, m, needL, m, delta);
            inc(2 * v + 1, m + 1, r, m + 1, needR, delta);
        }
    }

    void inc(int needL, int needR, ll delta) {
        inc(1, 0, n - 1, needL, needR, delta);
    }

    ll getValue(int v, int l, int r, int pos) {
        if (l == r) {
            return t[v] + add[v];
        }
        push(v);
        int m = (l + r) / 2;
        if (pos <= m) {
            return getValue(2 * v, l, m, pos);
        } else {
            return getValue(2 * v + 1, m + 1, r, pos);
        }
    }

    ll getValue(int pos) {
        return getValue(1, 0, n - 1, pos);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        SegmentTree t(a);
        while (Q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int L, R;
                ll delta;
                cin >> L >> R >> delta;
                L--; R--;
                t.inc(L, R, delta);
            } else {
                int pos;
                cin >> pos;
                pos--;
                cout << t.getValue(pos) << '\n';
            }
        }
    }
}
