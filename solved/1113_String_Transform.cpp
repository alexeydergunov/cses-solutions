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
        const int n = sz(s) - 1;

        vector<pair<char, int>> v;
        v.reserve(n + 1);
        vector<int> cnt(26);
        for (int i = 0; i <= n; i++) {
            const char c = s[i];
            if (c == '#') {
                v.emplace_back('#', 0);
            } else {
                assert('a' <= c && c <= 'z');
                v.emplace_back(c, cnt[c - 'a']);
                cnt[c - 'a']++;
            }
        }

        vector<pair<char, int>> sorted = v;
        sort(all(sorted));

        pair<char, int> now = {'#', 0};
        string ans;
        for (int i = 0; i < n; i++) {
            const int nextIndex = int(lower_bound(all(sorted), now) - sorted.begin());
            const pair<char, int> next = v[nextIndex];
            assert(next.first != '#');
            ans += next.first;
            now = next;
        }
        reverse(all(ans));

        cout << ans << '\n';
    }
}
