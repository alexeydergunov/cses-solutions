#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        const int maxS = n * (n + 1) / 2;

        vector<int> dpCur(2 * maxS + 1);
        dpCur[maxS] = 1;
        for (int x = 1; x <= n; x++) {
            vector<int> dpNext(2 * maxS + 1);
            for (int diff = -maxS; diff <= maxS; diff++) {
                if (diff - x >= -maxS) {
                    add(dpNext[maxS + diff - x], dpCur[maxS + diff]);
                }
                if (diff + x <= maxS) {
                    add(dpNext[maxS + diff + x], dpCur[maxS + diff]);
                }
            }
            dpCur.swap(dpNext);
        }

        const int ans = dpCur[maxS];
        cout << (ll)ans * ((MOD + 1) / 2) % MOD << '\n'; // (ans / 2)
    }
}
