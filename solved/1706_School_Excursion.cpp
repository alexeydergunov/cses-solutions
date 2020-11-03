#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MAXN = 100000;

struct DSU {
    vector<int> p;
    vector<int> s;

    DSU(const int n) {
        p.resize(n);
        iota(all(p), 0);
        s.assign(n, 1);
    }

    int find(const int x) {
        if (x == p[x]) return x;
        return p[x] = find(p[x]);
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        p[x] = y;
        s[y] += s[x];
    }
};

vector<int> normalizeWeights(const vector<int>& w) {
    map<int, int> mp;
    for (const int x : w) {
        mp[x]++;
    }

    vector<int> newW;
    for (const auto [x, cnt] : mp) {
        // cnt 'x'-es -> log(cnt) 'x'-es
        // it doesn't change the knapsack result
        int now = 1;
        int rem = cnt;
        while (true) {
            if (now > rem) {
                break;
            }
            newW.push_back(now * x);
            rem -= now;
            now *= 2;
        }
        if (rem > 0) {
            newW.push_back(rem * x);
        }
    }
    assert(accumulate(all(w), 0) == accumulate(all(newW), 0));
    return newW;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m;
    while (cin >> n >> m) {
        DSU dsu(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            dsu.merge(x, y);
        }

        vector<int> w;
        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == i) {
                w.push_back(dsu.s[i]);
            }
        }
        assert(accumulate(all(w), 0) == n);
        w = normalizeWeights(w);

        bitset<MAXN + 1> dp;
        dp[0] = true;
        for (const int x : w) {
            dp |= dp << x;
        }

        for (int i = 1; i <= n; i++) {
            cout << int(dp[i]);
        }
        cout << '\n';
    }
}
