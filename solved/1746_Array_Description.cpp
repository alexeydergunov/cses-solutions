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

    int n, maxV;
    while (cin >> n >> maxV) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> dpCur(maxV + 1);
        if (a[0] == 0) {
            for (int v = 1; v <= maxV; v++) {
                dpCur[v] = 1;
            }
        } else {
            dpCur[a[0]] = 1;
        }

        for (int i = 1; i < n; i++) {
            vector<int> dpPrev = dpCur;
            dpCur.assign(maxV + 1, 0);

            int v1, v2;
            if (a[i] == 0) {
                v1 = 1;
                v2 = maxV;
            } else {
                v1 = v2 = a[i];
            }

            for (int v = v1; v <= v2; v++) {
                for (int prevV = max(1, v - 1); prevV <= min(maxV, v + 1); prevV++) {
                    add(dpCur[v], dpPrev[prevV]);
                }
            }
        }

        int sum = 0;
        for (int v = 1; v <= maxV; v++) {
            add(sum, dpCur[v]);
        }
        cout << sum << '\n';
    }
}
