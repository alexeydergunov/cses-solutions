#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> prufer(n - 2);
        for (int& x : prufer) {
            cin >> x;
            x--;
        }

        vector<int> deg(n, 1);
        for (const int x : prufer) {
            deg[x]++;
        }

        set<int> leaves;
        for (int x = 0; x < n; x++) {
            if (deg[x] == 1) {
                leaves.insert(x);
            }
        }

        vector<ii> edges;
        for (const int parent : prufer) {
            assert(deg[parent] >= 1);
            assert(!leaves.empty());
            const int leaf = *leaves.begin();
            leaves.erase(leaves.begin());
            edges.emplace_back(leaf, parent);
            deg[leaf]--;
            deg[parent]--;
            if (deg[parent] == 1) {
                leaves.insert(parent);
            }
        }
        assert(sz(leaves) == 2);
        edges.emplace_back(*leaves.begin(), *leaves.rbegin()); // last edge
        assert(sz(edges) == n - 1);

        for (const auto [x, y] : edges) {
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
    }
}
