#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

vector<int> prefixFunction(const string& s) {
    const int n = sz(s);
    vector<int> p(n);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s, t;
    while (cin >> s >> t) {
        vector<int> p = prefixFunction(t + "#" + s);
        int ans = 0;
        for (int i = sz(t) + 1; i < sz(p); i++) {
            if (p[i] == sz(t)) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
}
