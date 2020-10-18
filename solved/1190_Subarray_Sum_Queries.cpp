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
    vector<ll> pref, suff, sum, ans;

    SegmentTree(const vector<ll>& a) {
        n = sz(a);
        t.resize(4 * n + 1);
        pref.resize(4 * n + 1);
        suff.resize(4 * n + 1);
        sum.resize(4 * n + 1);
        ans.resize(4 * n + 1);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = sum[v] = a[l];
            pref[v] = suff[v] = ans[v] = max(t[v], 0LL);
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        combine(v);
    }

    void combine(int v) {
        const int lv = 2 * v;
        const int rv = 2 * v + 1;
        pref[v] = max(pref[lv], sum[lv] + pref[rv]);
        suff[v] = max(suff[lv] + sum[rv], suff[rv]);
        sum[v] = sum[lv] + sum[rv];
        ans[v] = max({ans[lv], ans[rv], suff[lv] + pref[rv], 0LL});
    }

    void setValue(int v, int l, int r, int pos, ll val) {
        if (l == r) {
            t[v] = sum[v] = val;
            pref[v] = suff[v] = ans[v] = max(t[v], 0LL);
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

    void setValue(int pos, ll val) {
        setValue(1, 0, n - 1, pos, val);
    }

    ll getMaxSubarraySum() {
        return ans[1];
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
            int pos;
            ll val;
            cin >> pos >> val;
            pos--;
            t.setValue(pos, val);
            cout << t.getMaxSubarraySum() << '\n';
        }
    }
}
