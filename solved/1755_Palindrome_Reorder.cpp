#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

string solve(const string& s) {
    vector<int> cnt(26);
    for (char c : s) {
        cnt[c - 'A']++;
    }

    char oddChar = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 != 0) {
            if (oddChar == 0) {
                oddChar = char(i + 'A');
            } else {
                return "NO SOLUTION";
            }
        }
    }

    string start;
    for (int i = 0; i < 26; i++) {
        const char c = char(i + 'A');
        if (c == oddChar) {
            continue;
        }
        assert(cnt[i] % 2 == 0);
        for (int j = 0; j < cnt[i] / 2; j++) {
            start += c;
        }
    }

    string end = start;
    reverse(all(end));

    string mid;
    if (oddChar != 0) {
        for (int j = 0; j < cnt[oddChar - 'A']; j++) {
            mid += oddChar;
        }
    }

    return start + mid + end;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        cout << solve(s) << '\n';
    }
}
