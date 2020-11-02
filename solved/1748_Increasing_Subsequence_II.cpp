#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos, int delta) {
        pos++; // 1-indexed
        while (pos <= n) {
            add(t[pos], delta);
            pos += pos & -pos;
        }
    }

    int sum(int r) {
        r++; // 1-indexed
        int res = 0;
        while (r > 0) {
            add(res, t[r]);
            r -= r & -r;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<ii> sorted;
        for (int i = 0; i < n; i++) {
            sorted.emplace_back(a[i], i);
        }
        sort(all(sorted));

        FenwickTree t(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            const int index = int(lower_bound(all(sorted), ii(a[i], -1)) - sorted.begin());
            int prevSum = t.sum(index - 1);
            add(prevSum, 1); // add self
            add(ans, prevSum);
            t.inc(index, prevSum);
        }
        cout << ans << '\n';
    }
}
