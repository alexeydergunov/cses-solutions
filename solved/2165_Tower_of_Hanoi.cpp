#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

// from a to c
void hanoi(int depth, int a, int b, int c) {
    if (depth == 0) {
        return;
    }
    hanoi(depth - 1, a, c, b);
    cout << a << ' ' << c << '\n';
    hanoi(depth - 1, b, a, c);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        cout << (1 << n) - 1 << '\n';
        hanoi(n, 1, 2, 3);
    }
}
