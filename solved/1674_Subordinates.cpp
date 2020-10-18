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
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            g[p].push_back(i);
        }

        vector<int> s(n);
        function<void(int)> dfs = [&](int x) {
            s[x] = 1;
            for (int y : g[x]) {
                dfs(y);
                s[x] += s[y];
            }
        };
        dfs(0);

        for (int val : s) {
            cout << val - 1 << ' ';
        }
        cout << '\n';
    }
}
