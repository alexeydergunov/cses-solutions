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
    ll maxW;
    while (cin >> n >> maxW) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(all(a));

        int pairs = 0;
        int j = n - 1;
        for (int i = 0; i < n; i++) {
            while (i < j && a[i] + a[j] > maxW) {
                j--;
            }
            if (i < j) {
                pairs++;
                j--;
            }
        }
        cout << n - pairs << '\n';
    }
}
