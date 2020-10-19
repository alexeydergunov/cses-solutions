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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        const int maxX = *max_element(all(a));
        vector<int> cnt(maxX + 1);
        for (const int x : a) {
            cnt[x]++;
        }

        int ans = -1;
        for (int d = maxX; d >= 1; d--) {
            int curCnt = 0;
            for (int x = d; x <= maxX; x += d) {
                curCnt += cnt[x];
            }
            if (curCnt >= 2) {
                ans = d;
                break;
            }
        }

        assert(ans != -1);
        cout << ans << '\n';
    }
}
