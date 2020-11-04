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

        vector<pair<int, char>> cntMap(26);
        for (int i = 0; i < 26; i++) {
            cntMap[i].second = char(i + 'A');
        }
        for (const char ch : s) {
            cntMap[ch - 'A'].first++;
        }

        string ans;
        for (int i = 0; i < n; i++) {
            // this sort can be linear - we should only find two maximums
            sort(all(cntMap), [](const pair<int, char>& p1, const pair<int, char>& p2) {
                if (p1.first != p2.first) return p1.first > p2.first;
                return p1.second < p2.second;
            });

            const int remSum = n - i - 1;
            const int mx1 = cntMap[0].first;
            const int mx2 = cntMap[1].first;
            auto can = [&](const char ch) {
                if (ch == cntMap[0].second) {
                    // it's a maximal char
                    if (mx1 - 1 > mx2) {
                        // it will remain maximal, we should be able to use it every even step
                        if (2 * (mx1 - 1) - 1 > remSum) {
                            return false;
                        }
                    } else {
                        // second maximum will become first maximum, we should be able to use it every odd step
                        if (2 * mx2 - 1 > remSum) {
                            return false;
                        }
                    }
                } else {
                    // it's not a maximal char, we shoule be able to use maximal char every odd step
                    if (2 * mx1 - 1 > remSum) {
                        return false;
                    }
                }
                return true;
            };

            int bestCI = -1;
            for (int ci = 0; ci < 26; ci++) {
                const auto [cnt, ch] = cntMap[ci];
                if (cnt == 0) {
                    break;
                }
                if (!ans.empty() && ch == ans.back()) {
                    continue;
                }
                if (can(ch)) {
                    if (bestCI == -1 || ch < cntMap[bestCI].second) {
                        bestCI = ci;
                    }
                }
            }
            if (bestCI == -1) {
                break;
            }
            assert(cntMap[bestCI].first > 0);
            cntMap[bestCI].first--;
            ans += cntMap[bestCI].second;
        }

        if (sz(ans) < n) {
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
}
