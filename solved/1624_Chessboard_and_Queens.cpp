#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int f(const vector<string>& field) {
    vector<bool> col(8);
    vector<bool> diag1(15);
    vector<bool> diag2(15);
    int ans = 0;
    function<void(int)> rec = [&](int r) {
        if (r == 8) {
            ans++;
            return;
        }
        for (int c = 0; c < 8; c++) {
            if (field[r][c] == '*') {
                continue;
            }
            if (!col[c] && !diag1[r + c] && !diag2[7 + r - c]) {
                col[c] = diag1[r + c] = diag2[7 + r - c] = true;
                rec(r + 1);
                col[c] = diag1[r + c] = diag2[7 + r - c] = false;
            }
        }
    };
    rec(0);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    vector<string> field(8);
    while (cin >> field[0]) {
        for (int i = 1; i < 8; i++) {
            cin >> field[i];
        }

        cout << f(field) << '\n';
    }
}
