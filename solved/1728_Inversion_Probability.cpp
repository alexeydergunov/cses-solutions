#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(6); cout.setf(ios::fixed); // they require exactly 6 decimal places
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> r(n);
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }

        vector<vector<ld>> p(n);
        for (int i = 0; i < n; i++) {
            p[i].resize(r[i] + 1);
        }

        ld ans = 0.0;
        for (int curIndex = 0; curIndex < n; curIndex++) {
            ld curAns = 0.0;
            for (int curNum = 1; curNum <= r[curIndex]; curNum++) {
                for (int prevIndex = 0; prevIndex < curIndex; prevIndex++) {
                    for (int prevNum = curNum + 1; prevNum <= r[prevIndex]; prevNum++) {
                        curAns += p[prevIndex][prevNum];
                    }
                }
                p[curIndex][curNum] = 1.0 / r[curIndex];
            }
            ans += curAns / r[curIndex];
        }
        cout << ans << '\n';
    }
}
