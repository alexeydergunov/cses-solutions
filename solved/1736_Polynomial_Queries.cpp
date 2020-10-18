#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

ll getArithmeticSum(const ll first, const ll diff, const int len) {
    const ll last = first + (len - 1) * diff;
    return (first + last) * len / 2;
}

struct SegmentTree {
    int n;
    vector<ll> first, diff; // arithmetic progression added to vertex
    vector<ll> sum;
    vector<int> len;

    SegmentTree(const vector<ll>& a) {
        n = sz(a);
        first.resize(4 * n + 1);
        diff.resize(4 * n + 1);
        sum.resize(4 * n + 1);
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
        return sum[v] + getArithmeticSum(first[v], diff[v], len[v]);
    }

    void push(const int v) {
        if (first[v] != 0 || diff[v] != 0) {
            first[2 * v] += first[v];
            diff[2 * v] += diff[v];
            first[2 * v + 1] += first[v] + diff[v] * len[2 * v];
            diff[2 * v + 1] += diff[v];
            sum[v] += getArithmeticSum(first[v], diff[v], len[v]);
            first[v] = 0;
            diff[v] = 0;
        }
    }

    void combine(const int v) {
        assert(first[v] == 0 && diff[v] == 0); // must be already pushed
        sum[v] = getSumInVertex(2 * v) + getSumInVertex(2 * v + 1);
    }

    void inc(const int v, const int l, const int r, const int needL, const int needR, const int firstAdd) {
        if (l == needL && r == needR) {
            first[v] += firstAdd;
            diff[v]++;
            return;
        }
        push(v);
        const int m = (l + r) / 2;
        if (needR <= m) {
            inc(2 * v, l, m, needL, needR, firstAdd);
        } else if (m + 1 <= needL) {
            inc(2 * v + 1, m + 1, r, needL, needR, firstAdd);
        } else {
            inc(2 * v, l, m, needL, m, firstAdd);
            inc(2 * v + 1, m + 1, r, m + 1, needR, firstAdd + (m - needL + 1));
        }
        combine(v);
    }

    void inc(const int needL, const int needR, const int firstAdd) {
        inc(1, 0, n - 1, needL, needR, firstAdd);
    }

    ll getSum(const int v, const int l, const int r, const int needL, const int needR) {
        if (l == needL && r == needR) {
            return getSumInVertex(v);
        }
        push(v);
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
            int type, L, R;
            cin >> type >> L >> R;
            L--; R--;
            if (type == 1) {
                t.inc(L, R, 1);
            } else {
                cout << t.getSum(L, R) << '\n';
            }
        }
    }
}
