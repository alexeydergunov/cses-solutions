#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll INF = ll(1e18);

struct Cell {
    ll x, y;
};

pair<Cell, Cell> makeMove(const Cell& last, const char dir, const int delta) {
    Cell start = last;
    Cell finish = last;
    if (dir == 'R') { start.x++; finish.x += delta; }
    if (dir == 'L') { start.x--; finish.x -= delta; }
    if (dir == 'U') { start.y++; finish.y += delta; }
    if (dir == 'D') { start.y--; finish.y -= delta; }
    return {start, finish};
}

bool isInside(const Cell& O, Cell A, Cell B) {
    assert(A.x == B.x || A.y == B.y);
    if (O.x == A.x) {
        if (A.y > B.y) swap(A, B);
        return A.y <= O.y && O.y <= B.y;
    }
    if (O.y == A.y) {
        if (A.x > B.x) swap(A, B);
        return A.x <= O.x && O.x <= B.x;
    }
    return false;
}

// if we move from A to B, when we first intersect segment [C, D]?
ll getLengthBeforeIntersection(Cell A, Cell B, Cell C, Cell D) {
    assert(A.x == B.x || A.y == B.y);
    assert(C.x == D.x || C.y == D.y);

    // A == B
    if (A.x == B.x && A.y == B.y) {
        return isInside(A, C, D) ? 0 : INF;
    }

    // make first coordinate differ
    if (A.x == B.x) {
        swap(A.x, A.y);
        swap(B.x, B.y);
        swap(C.x, C.y);
        swap(D.x, D.y);
        return getLengthBeforeIntersection(A, B, C, D);
    }
    assert(A.x != B.x);
    assert(A.y == B.y);

    // move A to (0, 0)
    if (A.x != 0 || A.y != 0) {
        B.x -= A.x;
        C.x -= A.x;
        D.x -= A.x;
        B.y -= A.y;
        C.y -= A.y;
        D.y -= A.y;
        A = {0, 0};
        return getLengthBeforeIntersection(A, B, C, D);
    }
    assert(A.x == 0 && A.y == 0);
    assert(B.y == 0);

    // reflect so that B.first is positive
    if (B.x < 0) {
        B.x *= -1;
        C.x *= -1;
        D.x *= -1;
        return getLengthBeforeIntersection(A, B, C, D);
    }
    assert(B.x > 0);

    // now (A -> B) == ([0 0] -> [x, 0])
    if (C.y == D.y) {
        // these segments are parallel
        if (C.y != 0) {
            return INF;
        }
        if (C.x > D.x) {
            swap(C, D);
        }
        if (C.x >= 0) {
            if (C.x <= B.x) {
                return C.x;
            } else {
                return INF;
            }
        } else {
            if (D.x >= 0) {
                return 0;
            } else {
                return INF;
            }
        }
    } else {
        // these segments are perpendicular
        assert(C.x == D.x);
        if (C.x < 0 || C.x > B.x) {
            return INF;
        }
        if (C.y * D.y <= 0) {
            return C.x;
        } else {
            return INF;
        }
    }
}

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(const int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos, const int delta) {
        pos++; // 1-indexed
        while (pos <= n) {
            t[pos] += delta;
            pos += pos & -pos;
        }
    }

    int sum(int r) {
        r++; // 1-indexed
        int result = 0;
        while (r > 0) {
            result += t[r];
            r -= r & -r;
        }
        return result;
    }
};

const int OPEN = 0;
const int QUERY = 1;
const int CLOSE = 2;

struct Event {
    int type;
    ll x, y1, y2;
    int fenY1, fenY2;
    int index;

    Event() {}

    Event(int type_, ll x_, ll y1_, ll y2_, int index_) {
        type = type_;
        x = x_;
        y1 = y1_;
        y2 = y2_;
        index = index_;
    }

    bool operator < (const Event& e) const {
        if (x != e.x) return x < e.x;
        return type < e.type;
    }
};

struct Segment1D {
    ll L, R;
    int index;

    bool operator < (const Segment1D& seg) const {
        return R < seg.R;
    }
};

bool intersect1D(const vector<Segment1D>& v, const int segCnt) {
    if (sz(v) <= 1) {
        return false;
    }
    ll R = -INF;
    for (const Segment1D& seg : v) {
        if (seg.index >= segCnt) {
            // skipped by binary search
            continue;
        }
        if (seg.L <= R) {
            return true;
        }
        R = seg.R;
    }
    return false;
}

bool intersect2D(const vector<Event>& events, const int yCoordsCnt, const map<ll, vector<Segment1D>>& byX, const map<ll, vector<Segment1D>>& byY, const int segCnt) {
    for (auto& it : byX) {
        if (intersect1D(it.second, segCnt)) return true;
    }
    for (auto& it : byY) {
        if (intersect1D(it.second, segCnt)) return true;
    }

    // it's possible to do it with multiset, but fenwick tree is faster
    FenwickTree t(yCoordsCnt);
    for (const Event& e : events) {
        if (e.index >= segCnt) {
            // skipped by binary search
            continue;
        }
        if (e.type == OPEN) {
            t.inc(e.fenY1, 1);
        } else if (e.type == CLOSE) {
            t.inc(e.fenY1, -1);
        } else {
            const int s = t.sum(e.fenY2) - t.sum(e.fenY1 - 1);
            if (s > 0) {
                return true;
            }
        }
    }
    assert(t.sum(yCoordsCnt - 1) == 0);
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<pair<char, int>> v(n);
        for (auto& [c, d] : v) {
            cin >> c >> d;
        }

        // check opposite directions on two consecutive steps
        for (int i = 1; i < n; i++) {
            char c1 = v[i - 1].first;
            char c2 = v[i].first;
            bool fail = false;
            if (c1 == 'D' && c2 == 'U') fail = true;
            if (c1 == 'U' && c2 == 'D') fail = true;
            if (c1 == 'L' && c2 == 'R') fail = true;
            if (c1 == 'R' && c2 == 'L') fail = true;
            if (fail) {
                n = i;
                break;
            }
        }
        v.resize(n);

        // generate all segments
        vector<pair<Cell, Cell>> segments;
        Cell last{0, 0};
        for (int i = 0; i < n; i++) {
            pair<Cell, Cell> newSeg = makeMove(last, v[i].first, v[i].second);
            if (i == 0) {
                newSeg.first = Cell{0, 0}; // hack for first segment
            }
            segments.push_back(newSeg);
            last = newSeg.second;
        }
        assert(sz(segments) == n);

        // maps byX, byY - for parallel segments checking in binary search
        auto mpT1 = chrono::high_resolution_clock::now();
        map<ll, vector<Segment1D>> byX;
        map<ll, vector<Segment1D>> byY;
        for (int i = 0; i < n; i++) {
            auto [x1, y1] = segments[i].first;
            auto [x2, y2] = segments[i].second;
            if (x1 == x2) {
                if (y1 > y2) swap(y1, y2);
                byX[x1].emplace_back(Segment1D{y1, y2, i});
            } else {
                if (x1 > x2) swap(x1, x2);
                byY[y1].emplace_back(Segment1D{x1, x2, i});
            }
        }
        for (auto& it : byX) {
            sort(all(it.second));
        }
        for (auto& it : byY) {
            sort(all(it.second));
        }
        auto mpT2 = chrono::high_resolution_clock::now();
        auto mpTime = chrono::duration_cast<chrono::milliseconds>(mpT2 - mpT1).count();
        cerr << "Map time: " << mpTime << " ms" << endl;

        // events - for perpendicular segments checking in binary search
        auto evT1 = chrono::high_resolution_clock::now();
        vector<Event> events;
        events.reserve(3 * n);
        for (int i = 0; i < n; i++) {
            auto [x1, y1] = segments[i].first;
            auto [x2, y2] = segments[i].second;
            if (x1 == x2) {
                if (y1 > y2) swap(y1, y2);
                events.push_back(Event(QUERY, x1, y1, y2, i));
            } else {
                if (x1 > x2) swap(x1, x2);
                events.push_back(Event(OPEN, x1, y1, y2, i));
                events.push_back(Event(CLOSE, x2, y1, y2, i));
            }
        }
        sort(all(events));
        auto evT2 = chrono::high_resolution_clock::now();
        auto evTime = chrono::duration_cast<chrono::milliseconds>(evT2 - evT1).count();
        cerr << "Events time: " << evTime << " ms" << endl;

        // compression - for using fenwick tree instead of multiset in binary search
        auto comprT1 = chrono::high_resolution_clock::now();
        vector<ll> yCoords;
        yCoords.reserve(2 * sz(events));
        for (const Event& e : events) {
            yCoords.push_back(e.y1);
            yCoords.push_back(e.y2);
        }
        sort(all(yCoords));
        yCoords.resize(unique(all(yCoords)) - yCoords.begin());
        for (int i = 0; i < sz(yCoords) - 1; i++) {
            assert(yCoords[i] < yCoords[i + 1]);
        }
        for (Event& e : events) {
            e.fenY1 = int(lower_bound(all(yCoords), e.y1) - yCoords.begin());
            e.fenY2 = int(lower_bound(all(yCoords), e.y2) - yCoords.begin());
            assert(e.fenY1 <= e.fenY2);
        }
        auto comprT2 = chrono::high_resolution_clock::now();
        auto comprTime = chrono::duration_cast<chrono::milliseconds>(comprT2 - comprT1).count();
        cerr << "Compression time: " << comprTime << " ms" << endl;

        // find the maximal number of commands so there is no intersection
        auto bsT1 = chrono::high_resolution_clock::now();
        int left = 1;
        int right = n;
        int ansCnt = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (intersect2D(events, sz(yCoords), byX, byY, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
                ansCnt = mid;
            }
        }
        assert(ansCnt > 0);
        auto bsT2 = chrono::high_resolution_clock::now();
        auto bsTime = chrono::duration_cast<chrono::milliseconds>(bsT2 - bsT1).count();
        cerr << "Binary search time: " << bsTime << " ms" << endl;

        ll ans = 0;
        for (int i = 0; i < ansCnt; i++) {
            ans += v[i].second;
        }
        if (ansCnt == n) {
            cout << ans << '\n';
            continue;
        }

        // find the exact intersection
        auto postT1 = chrono::high_resolution_clock::now();
        const auto [A, B] = segments[ansCnt];
        ll minAdd = INF;
        for (int i = 0; i < ansCnt; i++) {
            const auto [C, D] = segments[i];
            const ll length = 1 + getLengthBeforeIntersection(A, B, C, D);
            minAdd = min(minAdd, length);
        }
        assert(minAdd < INF);
        auto postT2 = chrono::high_resolution_clock::now();
        auto postTime = chrono::duration_cast<chrono::milliseconds>(postT2 - postT1).count();
        cerr << "Postprocessing time: " << postTime << " ms" << endl;

        ans += minAdd;
        cout << ans << '\n';
    }
}
