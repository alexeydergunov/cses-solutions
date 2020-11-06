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
    ll maxS;
    while (cin >> n >> maxS) {
        vector<ll> a(2 * n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            a[i + n] = a[i];
        }

        vector<ll> pref = a;
        for (int i = 1; i < 2 * n; i++) {
            pref[i] += pref[i - 1];
        }

        int logN = 0;
        while (2 * (1 << logN) <= 2 * n + 1) {
            logN++;
        }

        vector<vector<int>> next(logN, vector<int>(2 * n + 1));
        for (int i = 0; i < 2 * n; i++) {
            const ll leftSum = (i == 0) ? 0 : pref[i - 1];
            const int j = int(upper_bound(all(pref), leftSum + maxS) - pref.begin());
            next[0][i] = j;
        }
        next[0][2 * n] = 2 * n; // fictive
        for (int z = 1; z < logN; z++) {
            for (int i = 0; i <= 2 * n; i++) {
                next[z][i] = next[z - 1][next[z - 1][i]];
            }
        }

        int bestAns = int(1e9);
        for (int start = 0; start < n; start++) {
            int curAns = 0;
            int i = start;
            for (int z = logN - 1; z >= 0; z--) {
                if (next[z][i] < start + n) {
                    curAns |= (1 << z);
                    i = next[z][i];
                }
            }
            curAns++; // we didn't count the last subarray
            bestAns = min(bestAns, curAns);
        }
        assert(bestAns <= n);
        cout << bestAns << '\n';
    }
}
