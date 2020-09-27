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

    string s;
    while (cin >> s) {
        int ans = 0;
        for (int i = 0; i < sz(s); ) {
            int j = i;
            while (j < sz(s) && s[i] == s[j]) {
                j++;
            }
            ans = max(ans, j - i);
            i = j;
        }
        cout << ans << '\n';
    }
}
