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
        deque<int> q(n);
        iota(all(q), 1);

        vector<int> ans;
        while (sz(q) > 1) {
            int x = q.front(); q.pop_front();
            int y = q.front(); q.pop_front();
            q.push_back(x);
            ans.push_back(y);
        }
        ans.push_back(q.front());
        assert(sz(ans) == n);

        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}
