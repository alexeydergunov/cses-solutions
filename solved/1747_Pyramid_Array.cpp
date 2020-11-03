#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos, const int delta) {
        pos++; // 1-indexed
        while (pos <= n) {
            t[pos] += delta;
            pos += pos & -pos;
        }
    }

    int sum(int r) {
        r++; // 1-indexed
        int res = 0;
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

    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> sorted = a;
        sort(all(sorted));
        sorted.resize(unique(all(sorted)) - sorted.begin());
        assert(sz(sorted) == n);

        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            a[i] = int(lower_bound(all(sorted), a[i]) - sorted.begin());
            pos[a[i]] = i;
        }

        FenwickTree t(n);
        for (int i = 0; i < n; i++) {
            t.inc(i, 1);
        }
        ll ans = 0;
        for (int x = 0; x < n; x++) {
            const int i = pos[x];
            const int leftSum = t.sum(i - 1);
            const int rightSum = t.sum(n - 1) - t.sum(i);
            ans += min(leftSum, rightSum);
            t.inc(i, -1);
        }
        cout << ans << '\n';
    }
}
