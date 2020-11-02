#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos) {
        pos++; // 1-indexed
        while (pos <= n) {
            t[pos]++;
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
            a[i]--;
        }

        // number of inversions
        ll ans1 = 0;
        FenwickTree t(n);
        for (int i = n - 1; i >= 0; i--) {
            ans1 += t.sum(a[i]);
            t.inc(a[i]);
        }

        // sum of (cycle length - 1)
        int ans2 = 0;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++) {
            if (!vis[a[i]]) {
                int cnt = 0;
                int x = a[i];
                while (true) {
                    cnt++;
                    vis[x] = true;
                    x = a[x];
                    if (vis[x]) break;
                }
                ans2 += cnt - 1;
            }
        }

        // don't touch longest increasing subsequence
        vector<int> d(n + 1, INF);
        for (int x : a) {
            *lower_bound(all(d), x) = x;
        }
        int lisLength = int(lower_bound(all(d), INF) - d.begin());
        int ans3 = n - lisLength;

        // don't touch some suffix
        int toMeet = n - 1;
        int skip = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] == toMeet) {
                toMeet--;
                skip++;
            }
        }
        int ans4 = n - skip;;

        cout << ans1 << ' ' << ans2 << ' ' << ans3 << ' ' << ans4 << '\n';
    }
}
