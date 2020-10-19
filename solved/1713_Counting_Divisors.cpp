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

    const int maxX = 1000 * 1000;
    vector<int> divs(maxX + 1);
    for (int i = 1; i <= maxX; i++) {
        for (int j = i; j <= maxX; j += i) {
            divs[j]++;
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        cout << divs[x] << '\n';
    }
}
