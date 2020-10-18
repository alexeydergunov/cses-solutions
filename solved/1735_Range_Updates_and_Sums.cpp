#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SegmentTree {
    int n;
    vector<ll> sum;
    vector<ll> add;
    vector<ll> val;
    vector<bool> isSet;
    vector<int> len;

    SegmentTree(const vector<ll>& a) {
        n = sz(a);
        sum.resize(4 * n + 1);
        add.resize(4 * n + 1);
        val.resize(4 * n + 1);
        isSet.resize(4 * n + 1);
        len.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(const int v, const int l, const int r, const vector<ll>& a) {
        len[v] = r - l + 1;
        if (l == r) {
            sum[v] = a[l];
            return;
        }
        const int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        combine(v);
    }

    ll getSumInVertex(const int v) {
        assert(len[v] > 0); // must be already calculated
        if (isSet[v]) {
            // if add[v] != 0, it was done after set query
            return (val[v] + add[v]) * len[v];
        } else {
            return sum[v] + add[v] * len[v];
        }
    }

    void push(const int v) {
        if (isSet[v]) {
            // here, if add[v] != 0, there was set query, then add query
            // and we need to overwrite children's add, not increase
            sum[v] = (val[v] + add[v]) * len[v];
            isSet[v] = false;
            if (len[v] > 1) {
                val[2 * v] = val[2 * v + 1] = val[v];
                isSet[2 * v] = isSet[2 * v + 1] = true;
                add[2 * v] = add[2 * v + 1] = add[v];
            }
            add[v] = 0;
        } else if (add[v] != 0) {
            sum[v] += add[v] * len[v];
            if (len[v] > 1) {
                add[2 * v] += add[v];
                add[2 * v + 1] += add[v];
            }
            add[v] = 0;
        }
        assert(!isSet[v]);
        assert(add[v] == 0);
    }

    void combine(const int v) {
        assert(len[v] > 1);
        // this vertex must be already pushed
        assert(!isSet[v]);
        assert(add[v] == 0);
        sum[v] = getSumInVertex(2 * v) + getSumInVertex(2 * v + 1);
    }

    void inc(const int v, const int l, const int r, const int needL, const int needR, const ll delta) {
        push(v);
        if (l == needL && r == needR) {
            add[v] += delta;
            return;
        }
        const int m = (l + r) / 2;
        if (needR <= m) {
            inc(2 * v, l, m, needL, needR, delta);
        } else if (m + 1 <= needL) {
            inc(2 * v + 1, m + 1, r, needL, needR, delta);
        } else {
            inc(2 * v, l, m, needL, m, delta);
            inc(2 * v + 1, m + 1, r, m + 1, needR, delta);
        }
        combine(v);
    }

    void inc(const int needL, const int needR, const ll delta) {
        inc(1, 0, n - 1, needL, needR, delta);
    }

    void setValue(const int v, const int l, const int r, const int needL, const int needR, const ll newValue) {
        push(v);
        if (l == needL && r == needR) {
            isSet[v] = true;
            val[v] = newValue;
            return;
        }
        const int m = (l + r) / 2;
        if (needR <= m) {
            setValue(2 * v, l, m, needL, needR, newValue);
        } else if (m + 1 <= needL) {
            setValue(2 * v + 1, m + 1, r, needL, needR, newValue);
        } else {
            setValue(2 * v, l, m, needL, m, newValue);
            setValue(2 * v + 1, m + 1, r, m + 1, needR, newValue);
        }
        combine(v);
    }

    void setValue(const int needL, const int needR, const ll newValue) {
        setValue(1, 0, n - 1, needL, needR, newValue);
    }

    ll getSum(const int v, const int l, const int r, const int needL, const int needR) {
        push(v);
        if (l == needL && r == needR) {
            return getSumInVertex(v);
        }
        const int m = (l + r) / 2;
        if (needR <= m) {
            return getSum(2 * v, l, m, needL, needR);
        }
        if (m + 1 <= needL) {
            return getSum(2 * v + 1, m + 1, r, needL, needR);
        }
        const ll sum1 = getSum(2 * v, l, m, needL, m);
        const ll sum2 = getSum(2 * v + 1, m + 1, r, m + 1, needR);
        return sum1 + sum2;
    }

    ll getSum(const int needL, const int needR) {
        return getSum(1, 0, n - 1, needL, needR);
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
        for (int q = 1; q <= Q; q++) {
            int type;
            cin >> type;
            if (type == 1) {
                int L, R;
                ll delta;
                cin >> L >> R >> delta;
                L--; R--;
                t.inc(L, R, delta);
            } else if (type == 2) {
                int L, R;
                ll newValue;
                cin >> L >> R >> newValue;
                L--; R--;
                t.setValue(L, R, newValue);
            } else {
                int L, R;
                cin >> L >> R;
                L--; R--;
                const ll ans = t.getSum(L, R);
                cout << ans << '\n';
            }
        }
    }
}
