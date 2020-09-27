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
        multiset<int> tickets;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            tickets.insert(x);
        }

        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            auto it = tickets.upper_bound(x);
            if (it == tickets.begin()) {
                cout << -1 << '\n';
                continue;
            }
            it--;
            cout << *it << '\n';
            tickets.erase(it);
        }
    }
}
