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
    ll S;
    while (cin >> n >> S) {
        vector<pair<ll, int>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(all(a));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                const ll toFind = S - a[i].first - a[j].first;
                int k = int(lower_bound(all(a), make_pair(toFind, -1)) - a.begin());
                while (k < n && (k == i || k == j)) {
                    k++;
                }
                if (k < n) {
                    if (a[k].first == toFind) {
                        cout << a[i].second + 1 << ' ' << a[j].second + 1 << ' ' << a[k].second + 1 << '\n';
                        goto end;
                    }
                }
            }
        }

        cout << "IMPOSSIBLE" << '\n';
        end:;
    }
}
