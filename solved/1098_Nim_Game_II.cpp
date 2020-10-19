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

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int xorSum = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            // the game with pile size x and moves [1, 2, 3] has grundy number (x % 4)
            xorSum ^= x % 4;
        }
        cout << ((xorSum != 0) ? "first" : "second") << '\n';
    }
}
