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

        const int maxS = accumulate(all(a), 0);
        vector<bool> dp(maxS + 1);
        dp[0] = true;
        for (const int x : a) {
            for (int s = maxS; s >= 0; s--) {
                if (dp[s] && s + x <= maxS) {
                    dp[s + x] = true;
                }
            }
        }

        vector<int> ans;
        for (int s = 1; s <= maxS; s++) {
            if (dp[s]) ans.push_back(s);
        }

        cout << sz(ans) << '\n';
        for (int s : ans) {
            cout << s << ' ';
        }
        cout << '\n';
    }
}
