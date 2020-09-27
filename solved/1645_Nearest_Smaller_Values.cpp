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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<ii> st;
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back().first >= a[i]) {
                st.pop_back();
            }
            if (st.empty()) {
                ans.push_back(0);
            } else {
                ans.push_back(st.back().second + 1);
            }
            st.emplace_back(a[i], i);
        }

        for (int i : ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
