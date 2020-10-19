#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

vector<int> zFunction(const string& s) {
    const int n = sz(s);
    vector<int> z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i <= R) {
            z[i] = min(R - i + 1, z[i - L]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        const int n = sz(s);
        vector<int> z = zFunction(s);

        vector<int> ans;
        for (int d = 1; d <= n; d++) {
            bool ok = true;
            for (int i = d; i + d <= n; i += d) {
                if (z[i] < d) {
                    ok = false;
                    break;
                }
            }
            if (n % d != 0) {
                if (z[n - n % d] < n % d) {
                    ok = false;
                }
            }
            if (ok) {
                ans.push_back(d);
            }
        }

        for (int val : ans) {
            cout << val << ' ';
        }
        cout << '\n';
    }
}
