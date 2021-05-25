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
        for (int& x : a) {
            cin >> x;
            x--;
        }

        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[a[i]] = i;
        }

        int ans = 1;
        for (int i = 1; i < n; i++) {
            if (pos[i - 1] > pos[i]) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
}
