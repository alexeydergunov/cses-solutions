#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct SegmentTree {
    int n;
    vector<ll> t;
    vector<int> maxIndex;

    SegmentTree(const vector<ll>& a) {
        n = sz(a);
        t.resize(4 * n + 1);
        maxIndex.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            maxIndex[v] = l;
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        combine(v);
    }

    void combine(int v) {
        if (t[2 * v] >= t[2 * v + 1]) {
            t[v] = t[2 * v];
            maxIndex[v] = maxIndex[2 * v];
        } else {
            t[v] = t[2 * v + 1];
            maxIndex[v] = maxIndex[2 * v + 1];
        }
    }

    pair<ll, int> getLowerBound(int v, int l, int r, ll x) {
        if (l == r) {
            if (t[v] >= x) {
                return {t[v], maxIndex[v]};
            } else {
                return {-INF, -1};
            }
        }
        int m = (l + r) / 2;
        if (t[2 * v] >= x) {
            return getLowerBound(2 * v, l, m, x);
        } else {
            return getLowerBound(2 * v + 1, m + 1, r, x);
        }
    }

    pair<ll, int> getLowerBound(ll x) {
        return getLowerBound(1, 0, n - 1, x);
    }

    void inc(int v, int l, int r, int pos, ll delta) {
        if (l == r) {
            t[v] += delta;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) {
            inc(2 * v, l, m, pos, delta);
        } else {
            inc(2 * v + 1, m + 1, r, pos, delta);
        }
        combine(v);
    }

    void inc(int pos, ll delta) {
        inc(1, 0, n - 1, pos, delta);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        SegmentTree t(a);

        for (int i = 0; i < m; i++) {
            ll x;
            cin >> x;
            auto [value, index] = t.getLowerBound(x); // index == -1 if not found
            cout << index + 1 << ' ';
            if (index >= 0) {
                assert(value >= x);
                t.inc(index, -x);
            }
        }
        cout << '\n';
    }
}
