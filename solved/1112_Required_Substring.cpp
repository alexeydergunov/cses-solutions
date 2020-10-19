#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MOD = int(1e9) + 7;

inline void add(int& x, const int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

vector<vector<int>> buildAutomata(const string& s) {
    const int n = sz(s);
    vector<vector<int>> automata(n + 1, vector<int>(26));
    for (int matched = 0; matched <= n; matched++) {
        for (char nextCh = 'A'; nextCh <= 'Z'; nextCh++) {
            const string t = s.substr(0, matched) + nextCh;
            int newMatched = min(n, sz(t));
            while (newMatched > 0) {
                const string prefS = s.substr(0, newMatched);
                const string suffT = t.substr(sz(t) - newMatched, newMatched);
                if (prefS == suffT) {
                    break;
                }
                newMatched--;
            }
            automata[matched][nextCh - 'A'] = newMatched;
        }
    }
    return automata;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        string s;
        cin >> s;

        const vector<vector<int>>& automata = buildAutomata(s);

        // (index, current characters matched, was already matched or not)
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(sz(s) + 1, vector<int>(2)));
        dp[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int matched = 0; matched <= sz(s); matched++) {
                for (int was = 0; was <= 1; was++) {
                    for (char c = 'A'; c <= 'Z'; c++) {
                        int newMatched = automata[matched][c - 'A'];
                        int newWas = (was == 1 || newMatched == sz(s)) ? 1 : 0;
                        add(dp[i + 1][newMatched][newWas], dp[i][matched][was]);
                    }
                }
            }
        }

        int ans = 0;
        for (int matched = 0; matched <= sz(s); matched++) {
            add(ans, dp[n][matched][1]);
        }
        cout << ans << '\n';
    }
}
