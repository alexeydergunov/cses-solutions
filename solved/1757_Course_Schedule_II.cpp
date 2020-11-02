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

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> revG(n);
        vector<int> revInDeg(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            revG[y].push_back(x);
            revInDeg[x]++;
        }

        // build answer from the end, with a reversed graph
        priority_queue<int> pq; // max heap
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (revInDeg[i] == 0) {
                pq.push(i);
            }
        }
        while (!pq.empty()) {
            const int x = pq.top(); pq.pop();
            ans.push_back(x);
            for (const int y : revG[x]) {
                revInDeg[y]--;
                if (revInDeg[y] == 0) {
                    pq.push(y);
                }
            }
        }
        assert(sz(ans) == n);
        reverse(all(ans));

        for (const int x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}
