#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

inline bool hasBit(const int x, const int bit) {
    return (x & (1 << bit)) != 0;
}

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

        const int maxV = *max_element(all(a));
        int logV = 0;
        while ((1 << logV) <= maxV) {
            logV++;
        }

        vector<int> cnt(1 << logV);
        for (const int x : a) {
            cnt[x]++;
        }

        vector<int> cntSub = cnt; // cntSub[mask] -> cnt for all submasks of mask
        for (int bit = 0; bit < logV; bit++) {
            for (int x = 0; x < (1 << logV); x++) {
                if (!hasBit(x, bit)) {
                    cntSub[x | (1 << bit)] += cntSub[x]; // push to mask with this bit set
                }
            }
        }

        vector<int> cntOver = cnt; // cntOver[mask] -> cnt for all overmasks of mask
        for (int bit = 0; bit < logV; bit++) {
            for (int x = (1 << logV) - 1; x >= 0; x--) {
                if (hasBit(x, bit)) {
                    cntOver[x & ~(1 << bit)] += cntOver[x]; // push to mask without this bit set
                }
            }
        }

        const int allMask = (1 << logV) - 1;
        for (const int x : a) {
            cout << cntSub[x] << ' ' << cntOver[x] << ' ' << (n - cntSub[x ^ allMask]) << '\n';
        }
    }
}
