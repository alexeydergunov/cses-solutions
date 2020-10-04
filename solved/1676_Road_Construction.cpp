#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct DSU {
    int cnt;
    int largest;
    vector<int> p;
    vector<int> s;

    DSU(int n) {
        cnt = n;
        largest = 1;
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
        if (s[x] > s[y]) {
            swap(x, y);
        }
        // now s[x] <= s[y]
        p[x] = y;
        s[y] += s[x];
        cnt--;
        largest = max(largest, s[y]);
    }
};

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
            cout << dsu.cnt << ' ' << dsu.largest << '\n';
        }
    }
}
