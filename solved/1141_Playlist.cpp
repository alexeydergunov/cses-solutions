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

        int ans = 0;
        set<int> s;
        int L = 0;
        for (int R = 0; R < n; R++) {
            if (s.count(a[R])) {
                while (L < R) {
                    const int deleted = a[L];
                    assert(s.count(deleted));
                    s.erase(deleted);
                    L++;
                    if (deleted == a[R]) {
                        break;
                    }
                }
                assert(L <= R);
                assert(!s.count(a[R]));
            }
            s.insert(a[R]);
            ans = max(ans, R - L + 1);
        }
        cout << ans << '\n';
    }
}
