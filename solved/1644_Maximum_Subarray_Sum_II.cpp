#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct SegTree {
    int n;
    vector<ll> t;

    SegTree(const vector<ll>& a) {
        n = sz(a);
        t.assign(4 * n + 1, INF);
        build(1, 0, n - 1, a);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        const int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }

    ll getMin(int v, int l, int r, int needL, int needR) {
        if (l == needL && r == needR) {
            return t[v];
        }
        const int m = (l + r) / 2;
        if (needR <= m) {
            return getMin(2 * v, l, m, needL, needR);
        }
        if (m + 1 <= needL) {
            return getMin(2 * v + 1, m + 1, r, needL, needR);
        }
        ll res1 = getMin(2 * v, l, m, needL, m);
        ll res2 = getMin(2 * v + 1, m + 1, r, m + 1, needR);
        return min(res1, res2);
    }

    ll getMin(int needL, int needR) {
        assert(0 <= needL);
        assert(needL <= needR);
        assert(needR < n);
        return getMin(1, 0, n - 1, needL, needR);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, len1, len2;
    while (cin >> n >> len1 >> len2) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<ll> pref(n + 1); // 1-indexed
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + a[i];
        }
        SegTree st(pref);

        ll ans = -INF;
        for (int r = 1; r <= n; r++) { // 1-indexed
            // sum == pref[r] - pref[l - 1]
            // sum == pref[r] - min{pref[r - len2], ..., pref[r - len1]}
            int ql = r - len2;
            int qr = r - len1;
            assert(ql <= qr);
            if (qr < 0) {
                continue;
            }

            ql = max(ql, 0);
            const ll sub = st.getMin(ql, qr);
            ans = max(ans, pref[r] - sub);
        }
        assert(ans > -INF);
        cout << ans << '\n';
    }
}
