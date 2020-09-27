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
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (n == 2 || n == 3) {
            cout << "NO SOLUTION" << '\n';
            continue;
        }
        vector<int> ans;
        for (int x = 2; x <= n; x += 2) {
            ans.push_back(x);
        }
        for (int x = 1; x <= n; x += 2) {
            ans.push_back(x);
        }
        assert(sz(ans) == n);
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}
