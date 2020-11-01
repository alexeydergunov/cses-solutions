#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int MAX_COORD = int(1e6);

const int OPEN = 0;
const int QUERY = 1;
const int CLOSE = 2;

struct Event {
    int type, x, y1, y2;
};

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos, int delta) {
        pos++; // 1-indexed
        while (pos <= n) {
            t[pos] += delta;
            pos += pos & -pos;
        }
    }

    int sum(int r) {
        r++; // 1-indexed
        int res = 0;
        while (r > 0) {
            res += t[r];
            r -= r & -r;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<Event> events;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1 += MAX_COORD;
            y1 += MAX_COORD;
            x2 += MAX_COORD;
            y2 += MAX_COORD;
            if (x1 == x2) {
                if (y1 > y2) swap(y1, y2);
                events.push_back(Event{QUERY, x1, y1, y2});
            } else {
                assert(y1 == y2);
                if (x1 > x2) swap(x1, x2);
                events.push_back(Event{OPEN, x1, y1, y2});
                events.push_back(Event{CLOSE, x2, y1, y2});
            }
        }
        sort(all(events), [](const Event& e1, const Event& e2) {
            if (e1.x != e2.x) return e1.x < e2.x;
            return e1.type < e2.type;
        });

        FenwickTree t(2 * MAX_COORD + 1);
        ll ans = 0;
        for (const Event& e : events) {
            if (e.type == OPEN) {
                t.inc(e.y1, 1);
            } else if (e.type == CLOSE) {
                t.inc(e.y1, -1);
            } else {
                ans += t.sum(e.y2) - t.sum(e.y1 - 1);
            }
        }
        cout << ans << '\n';
    }
}
