#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int grayCode(int x) {
    return x ^ (x >> 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        for (int x = 0; x < (1 << n); x++) {
            int g = grayCode(x);
            for (int i = n - 1; i >= 0; i--) {
                cout << ((g >> i) & 1);
            }
            cout << '\n';
        }
    }
}
