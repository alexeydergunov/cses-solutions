#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct FenwickTree {
    int n;
    vector<ll> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int i, const ll delta) {
        i++; // make 1-indexed
        while (i <= n) {
            t[i] += delta;
            i += i & -i;
        }
    }

    ll get(int r) {
        r++; // make 1-indexed
        ll res = 0;
        while (r > 0) {
            res += t[r];
            r -= r & -r;
        }
        return res;
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

        FenwickTree t(n);
        for (int i = 0; i < n; i++) {
            t.inc(i, a[i]);
        }

        while (Q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int pos;
                ll value;
                cin >> pos >> value;
                pos--;
                const ll delta = value - a[pos];
                t.inc(pos, delta);
                a[pos] = value;
            } else {
                int L, R;
                cin >> L >> R;
                L--; R--;
                cout << t.get(R) - t.get(L - 1) << '\n';
            }
        }
    }
}
