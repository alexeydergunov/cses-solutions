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

    void inc(int i, const int delta) {
        i++; // make 1-indexed
        while (i <= n) {
            t[i] += delta;
            i += i & -i;
        }
    }

    int sum(int r) {
        r++; // make 1-indexed
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

    int n, Q;
    while (cin >> n >> Q) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<tuple<char, int, int>> queries;
        while (Q--) {
            char c;
            int z1, z2;
            cin >> c >> z1 >> z2;
            queries.emplace_back(c, z1, z2);
        }

        vector<int> coords;
        for (const int x : a) {
            coords.push_back(x);
        }
        for (const auto [c, z1, z2] : queries) {
            if (c == '!') {
                coords.push_back(z2);
            } else {
                coords.push_back(z1);
                coords.push_back(z2);
            }
        }
        sort(all(coords));
        coords.resize(unique(all(coords)) - coords.begin());
        auto getCoord = [&](const int x) {
            return int(lower_bound(all(coords), x) - coords.begin());
        };

        FenwickTree t(sz(coords));
        for (int i = 0; i < n; i++) {
            a[i] = getCoord(a[i]); // change to compressed
            t.inc(a[i], 1);
        }

        for (const auto [c, z1, z2] : queries) {
            if (c == '!') {
                const int pos = z1 - 1;
                const int oldX = a[pos];
                const int newX = getCoord(z2);
                t.inc(oldX, -1);
                t.inc(newX, 1);
                a[pos] = newX;
            } else {
                const int L = getCoord(z1);
                const int R = getCoord(z2);
                cout << t.sum(R) - t.sum(L - 1) << '\n';
            }
        }
    }
}
