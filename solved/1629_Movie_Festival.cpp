#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Segment {
    int L, R;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<Segment> segments(n);
        for (auto& s : segments) {
            cin >> s.L >> s.R;
        }
        sort(all(segments), [](const Segment& e1, const Segment& e2) {
            return e1.R < e2.R;
        });

        int ans = 0;
        int curR = 0;
        for (const auto& s : segments) {
            if (curR <= s.L) {
                ans++;
                curR = s.R;
            }
        }
        cout << ans << '\n';
    }
}
