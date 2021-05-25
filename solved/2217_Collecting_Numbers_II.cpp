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

    int n, q;
    while (cin >> n >> q) {
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
        for (int x = 1; x < n; x++) {
            if (pos[x - 1] > pos[x]) {
                ans++;
            }
        }

        auto doSwap = [&](int i, int j) {
            int x = a[i];
            int y = a[j];
            if (x > y) {
                swap(x, y);
                swap(i, j);
            }
            if (x - 1 >= 0 && pos[x - 1] > pos[x]) ans--;
            if (x + 1 < n && pos[x] > pos[x + 1]) ans--;
            if (x + 1 != y && y - 1 >= 0 && pos[y - 1] > pos[y]) ans--; // don't subtract if x + 1 == y
            if (y + 1 < n && pos[y] > pos[y + 1]) ans--;
            pos[x] = j;
            pos[y] = i;
            a[i] = y;
            a[j] = x;
            if (x - 1 >= 0 && pos[x - 1] > pos[x]) ans++;
            if (x + 1 < n && pos[x] > pos[x + 1]) ans++;
            if (x + 1 != y && y - 1 >= 0 && pos[y - 1] > pos[y]) ans++; // don't add if x + 1 == y
            if (y + 1 < n && pos[y] > pos[y + 1]) ans++;
        };

        while (q--) {
            int i, j;
            cin >> i >> j;
            i--; j--;
            doSwap(i, j);
            cout << ans << '\n';
        }
    }
}
