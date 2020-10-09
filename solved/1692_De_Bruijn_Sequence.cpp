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

    int n;
    while (cin >> n) {
        const int maxLen = (1 << n) + n - 1;
        vector<bool> used(1 << n);
        vector<int> st;
        // start with n zeroes
        string s(n, '0');
        st.push_back(0);
        used[0] = true;
        function<void()> rec = [&]() {
            assert(sz(s) <= maxLen);
            if (sz(s) == maxLen) {
                return;
            }
            const int lastBits = st.back() & ~(1 << (n - 1));
            for (int add = 0; add <= 1; add++) {
                const int newNum = (lastBits << 1) + add;
                if (!used[newNum]) {
                    used[newNum] = true;
                    st.push_back(newNum);
                    s += char(add + '0');
                    rec();
                    if (sz(s) == maxLen) {
                        return;
                    }
                    used[newNum] = false;
                    st.pop_back();
                    s.pop_back();
                }
            }
        };
        rec();
        assert(sz(st) == (1 << n));
        assert(sz(s) == maxLen);
        cout << s << '\n';
    }
}
