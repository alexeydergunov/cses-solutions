#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Segment {
    int L, R;

    bool operator < (const Segment& s) const {
        return R < s.R;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<Segment> segments(n); // sorted by L
        for (Segment& seg : segments) {
            cin >> seg.L >> seg.R;
        }
        sort(all(segments), [](const Segment& s1, const Segment& s2) {
            return s1.L < s2.L;
        });

        multiset<Segment> segSet; // sorted by R
        for (const Segment& seg : segments) {
            segSet.insert(seg);
        }

        int maxCoord = -1;
        for (const Segment& seg : segments) {
            maxCoord = max(maxCoord, seg.R);
        }
        assert(maxCoord > 0);
        int logCoord = 0;
        while ((1 << logCoord) < maxCoord + 1) {
            logCoord++;
        }

        vector<vector<int>> next(logCoord, vector<int>(maxCoord + 2, maxCoord + 1));
        int ptr = 0;
        for (int x = 0; x <= maxCoord; x++) {
            if (!segSet.empty()) {
                next[0][x] = segSet.begin()->R;
            }
            while (ptr < n && segments[ptr].L <= x) {
                segSet.erase(segSet.find(segments[ptr]));
                ptr++;
            }
        }
        assert(segSet.empty());

        for (int z = 1; z < logCoord; z++) {
            for (int x = 0; x <= maxCoord; x++) {
                next[z][x] = next[z - 1][next[z - 1][x]];
            }
        }

        while (Q--) {
            int L, R;
            cin >> L >> R;
            int ans = 0;
            for (int z = logCoord - 1; z >= 0; z--) {
                if (next[z][L] <= R) {
                    ans |= (1 << z);
                    L = next[z][L];
                }
            }
            cout << ans << '\n';
        }
    }
}
