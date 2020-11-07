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

int smart(const vector<int>& a, const int maxS) {
    const int n = sz(a);
    const int sumA = accumulate(all(a), 0);

    // dp[i][s] - number of ways to form groups,
    // such that there are i opened groups and current sum is s (s is shifted: [-sumA..sumA] -> [0..2*sumA])
    // when we open a group, we decrease s, when we close it - increase s
    // it's important that array a is sorted
    const int SHIFT = sumA;
    vector<vector<int>> dpCur(1, vector<int>(2 * sumA + 1));
    dpCur[0][SHIFT] = 1;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> dpNext(sz(dpCur) + 1, vector<int>(2 * sumA + 1));
        for (int g = 0; g <= i; g++) {
            for (int s = -sumA; s <= sumA; s++) {
                const int curValue = dpCur[g][s + SHIFT];
                // open new group and close it immediately
                add(dpNext[g][s + SHIFT], curValue);
                // open new group and don't close it
                if (s - a[i] >= -sumA) {
                    add(dpNext[g + 1][s - a[i] + SHIFT], curValue);
                }
                if (g > 0) {
                    const int ways = int(curValue * ll(g) % MOD);
                    // close one of g existing groups
                    if (s + a[i] <= sumA) {
                        add(dpNext[g - 1][s + a[i] + SHIFT], ways);
                    }
                    // attach to one of g opened groups, but don't close it
                    add(dpNext[g][s + SHIFT], ways);
                }
            }
        }
        dpCur.swap(dpNext);
    }

    int ans = 0;
    for (int s = 0; s <= maxS; s++) {
        add(ans, dpCur[0][s + SHIFT]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, maxS;
    while (cin >> n >> maxS) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(all(a));

        const int ans = smart(a, maxS);
        cout << ans << '\n';
    }
}
