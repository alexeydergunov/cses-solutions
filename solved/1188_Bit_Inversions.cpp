#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

struct Segment {
    int L, R, value;

    bool operator < (const Segment& s) const {
        if (L != s.L) return L < s.L;
        return R < s.R;
    }

    int length() const {
        return R - L;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        set<Segment> segments;
        multiset<int> lengths;

        auto insert = [&](const Segment& seg) {
            segments.insert(seg);
            lengths.insert(seg.length());
        };
        auto erase = [&](const Segment& seg) {
            segments.erase(seg);
            lengths.erase(lengths.find(seg.length()));
        };

        for (int i = 0; i < sz(s); ) {
            int j = i;
            while (j < sz(s) && s[i] == s[j]) {
                j++;
            }
            Segment seg{i, j, s[i] - '0'};
            insert(seg);
            i = j;
        }

        auto flip = [&](const int pos) {
            auto it = segments.lower_bound(Segment{pos, INF, -1});
            assert(it != segments.begin());
            it--;
            const Segment seg = *it;
            assert(seg.L <= pos && pos < seg.R);
            erase(seg);

            Segment newSegWithPos{pos, pos + 1, seg.value ^ 1};
            insert(newSegWithPos);

            if (seg.L < pos) {
                insert(Segment{seg.L, pos, seg.value});
            } else {
                // merge flipped point with left segment
                auto leftIt = segments.find(newSegWithPos);
                if (leftIt != segments.begin()) {
                    leftIt--;
                    const Segment leftSeg = *leftIt;
                    assert(leftSeg.R == newSegWithPos.L);
                    assert(leftSeg.value == newSegWithPos.value);
                    erase(leftSeg);
                    erase(newSegWithPos);
                    newSegWithPos.L = leftSeg.L;
                    insert(newSegWithPos);
                }
            }

            if (pos + 1 < seg.R) {
                insert(Segment{pos + 1, seg.R, seg.value});
            } else {
                // merge flipped point with right segment
                auto rightIt = segments.find(newSegWithPos);
                rightIt++;
                if (rightIt != segments.end()) {
                    const Segment rightSeg = *rightIt;
                    assert(rightSeg.L == newSegWithPos.R);
                    assert(rightSeg.value == newSegWithPos.value);
                    erase(rightSeg);
                    erase(newSegWithPos);
                    newSegWithPos.R = rightSeg.R;
                    insert(newSegWithPos);
                }
            }
        };

        int Q;
        cin >> Q;
        while (Q--) {
            int pos;
            cin >> pos;
            pos--;
            flip(pos);
            cout << *lengths.rbegin() << ' ';
        }
        cout << '\n';
    }
}
