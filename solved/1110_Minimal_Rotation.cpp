#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

// copypasted from e-maxx
int minCyclicShift(string s) { // passed by value
    s += s;
    const int n = sz(s);
    int ans = 0;
    for (int i = 0; i < n / 2; ) {
        ans = i;
        int j = i + 1;
        int k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        const int n = sz(s);
        const int shift = minCyclicShift(s);
        string ans = s.substr(shift, n - shift) + s.substr(0, shift);
        assert(sz(ans) == n);
        cout << ans << '\n';
    }
}
