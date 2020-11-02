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

    ll sumX;
    int n;
    while (cin >> sumX >> n) {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            pq.push(x);
        }

        ll ans = 0;
        while (sz(pq) > 1) {
            const ll x1 = pq.top(); pq.pop();
            const ll x2 = pq.top(); pq.pop();
            const ll newX = x1 + x2;
            ans += newX;
            pq.push(newX);
        }
        cout << ans << '\n';
    }
}
