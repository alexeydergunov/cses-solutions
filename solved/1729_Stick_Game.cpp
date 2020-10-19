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

    int n, k;
    while (cin >> n >> k) {
        vector<int> moves(k);
        for (int i = 0; i < k; i++) {
            cin >> moves[i];
        }

        vector<bool> isWin(n + 1);
        for (int i = 0; i < n; i++) {
            if (!isWin[i]) {
                for (const int move : moves) {
                    if (i + move <= n) {
                        isWin[i + move] = true;
                    }
                }
            }
        }

        string ans;
        for (int i = 1; i <= n; i++) {
            ans += (isWin[i] ? 'W' : 'L');
        }
        cout << ans << '\n';
    }
}
