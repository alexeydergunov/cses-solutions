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

    string s;
    while (cin >> s) {
        const int n = sz(s);

        map<char, vector<int>> positions;
        for (int i = 0; i < n; i++) {
            positions[s[i]].push_back(i);
        }

        string ans;
        int pos = -1;
        while (true) {
            char bestChar = 0;
            int bestPos = -1;
            for (const auto& [c, v] : positions) {
                const auto it = upper_bound(all(v), pos);
                const int newPos = (it == v.end()) ? n : *it;
                if (newPos > bestPos) {
                    bestChar = c;
                    bestPos = newPos;
                }
            }
            assert(bestPos != -1);
            ans += bestChar;
            pos = bestPos;
            if (pos >= n) break;
        }
        cout << ans << '\n';
    }
}
