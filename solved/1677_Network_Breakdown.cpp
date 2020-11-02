#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct DSU {
    int cnt;
    vector<int> p;

    DSU(int n) {
        p.resize(n);
        iota(all(p), 0);
        cnt = n;
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
        cnt--;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<ii> edges(m);
        for (auto& [x, y] : edges) {
            cin >> x >> y;
            x--; y--;
            if (x > y) swap(x, y);
        }

        vector<ii> removedEdges(k);
        for (auto& [x, y] : removedEdges) {
            cin >> x >> y;
            x--; y--;
            if (x > y) swap(x, y);
        }

        // add all existing edges to DSU
        DSU dsu(n);
        vector<ii> sortedRemovedEdges = removedEdges;
        sort(all(sortedRemovedEdges));
        for (const auto& e : edges) {
            if (!binary_search(all(sortedRemovedEdges), e)) {
                dsu.merge(e.first, e.second);
            }
        }

        // in reverse order, removed edges become added edges
        vector<int> ans;
        reverse(all(removedEdges));
        for (const auto& e : removedEdges) {
            ans.push_back(dsu.cnt);
            dsu.merge(e.first, e.second);
        }
        reverse(all(ans));

        for (const int val : ans) {
            cout << val << ' ';
        }
        cout << '\n';
    }
}
