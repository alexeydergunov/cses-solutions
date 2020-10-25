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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        const int sum = accumulate(all(a), 0);

        priority_queue<ii> pq; // (a[i], i) desc
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                pq.emplace(a[i], i);
            }
        }

        vector<ii> ans;
        bool fail = false;
        while (!pq.empty()) {
            ii p1 = pq.top(); pq.pop();
            assert(p1.first > 0);
            if (sz(pq) < p1.first) {
                fail = true;
                break;
            }
            vector<ii> taken;
            for (int i = 0; i < p1.first; i++) {
                ii p2 = pq.top(); pq.pop();
                assert(p2.first > 0);
                taken.emplace_back(p2);
            }
            for (ii p2 : taken) {
                ans.emplace_back(p1.second, p2.second);
                p2.first--;
                if (p2.first > 0) {
                    pq.push(p2);
                }
            }
        }

        if (fail) {
            cout << "IMPOSSIBLE" << '\n';
        } else {
            assert(2 * sz(ans) == sum);
            cout << sz(ans) << '\n';
            for (const auto [x, y] : ans) {
                cout << x + 1 << ' ' << y + 1 << '\n';
            }
        }
    }
}
