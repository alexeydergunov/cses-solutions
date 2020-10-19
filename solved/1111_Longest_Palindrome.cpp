#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

// copypasted from cp-algorithms
vector<int> oddPalindromes(const string& s) {
    const int n = sz(s);
    vector<int> d(n);
    int L = 0, R = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > R) ? 1 : min(d[L + R - i], R - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d[i] = k--;
        if (i + k > R) {
            L = i - k;
            R = i + k;
        }
    }
    return d;
}

// copypasted from cp-algorithms
vector<int> evenPalindromes(const string& s) {
    const int n = sz(s);
    vector<int> d(n);
    int L = 0, R = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > R) ? 0 : min(d[L + R - i + 1], R - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d[i] = k--;
        if (i + k > R) {
            L = i - k - 1;
            R = i + k;
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        const int n = sz(s);
        const vector<int>& odd = oddPalindromes(s);
        const vector<int>& even = evenPalindromes(s);

        int ansLen = 0;
        int ansStart = -1;
        for (int i = 0; i < n; i++) {
            if (2 * odd[i] - 1 > ansLen) {
                ansLen = 2 * odd[i] - 1;
                ansStart = i - odd[i] + 1;
            }
            if (2 * even[i] > ansLen) {
                ansLen = 2 * even[i];
                ansStart = i - even[i];
            }
        }
        assert(ansStart != -1);
        assert(ansLen > 0);
        cout << s.substr(ansStart, ansLen) << '\n';
    }
}
