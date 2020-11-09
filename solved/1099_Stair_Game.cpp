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

    // (here indices are 0-based)
    // we should keep xor of all odd indices equal to 0
    // if the opponent moves some balls from odd index to even:
    //     we move from some odd index to even too, as in nim, keeping xor equal to 0
    // if the opponent moves some balls from even index to odd:
    //     we pass exactly these balls forward (from odd index to even), and xor is still 0
    // also, explanation on e-maxx: https://e-maxx.ru/algo/sprague_grundy#17

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int xorSum = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (i % 2 != 0) {
                xorSum ^= x;
            }
        }
        cout << ((xorSum != 0) ? "first" : "second") << '\n';
    }
}
