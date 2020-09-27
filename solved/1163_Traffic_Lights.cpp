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

    int maxX, n;
    while (cin >> maxX >> n) {
        set<int> coords;
        coords.insert(0);
        coords.insert(maxX);

        multiset<int> dist;
        dist.insert(maxX);

        auto add = [&](const int x) {
            auto itC = coords.upper_bound(x);
            assert(itC != coords.begin());
            assert(itC != coords.end());
            const int R = *itC;
            itC--;
            const int L = *itC;
            assert(L < x);
            assert(x < R);
            coords.insert(x);

            auto itD = dist.find(R - L);
            assert(itD != dist.end());
            assert(*itD == R - L);
            dist.erase(itD);
            dist.insert(x - L);
            dist.insert(R - x);
        };

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            add(x);
            cout << *dist.rbegin() << ' ';
        }
        cout << '\n';
    }
}
