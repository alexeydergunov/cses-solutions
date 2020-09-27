#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Event {
    int x, type, i;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<Event> events;
        events.reserve(2 * n);
        for (int i = 0; i < n; i++) {
            int L, R;
            cin >> L >> R;
            events.push_back(Event{L, 0, i});
            events.push_back(Event{R, 1, i});
        }
        sort(all(events), [](const Event& e1, const Event& e2) {
            if (e1.x != e2.x) return e1.x < e2.x;
            return e1.type < e2.type;
        });

        // rooms are 1-indexed
        int roomCnt = 0;
        set<int> freeRooms;
        set<int> usedRooms;
        vector<int> ans(n, -1);
        for (const Event& e : events) {
            if (e.type == 0) {
                int room;
                if (freeRooms.empty()) {
                    room = ++roomCnt;
                } else {
                    room = *freeRooms.begin();
                    freeRooms.erase(freeRooms.begin());
                }
                assert(!usedRooms.count(room));
                usedRooms.insert(room);
                ans[e.i] = room;
            } else {
                const int room = ans[e.i];
                assert(room != -1);
                assert(usedRooms.count(room));
                assert(!freeRooms.count(room));
                usedRooms.erase(room);
                freeRooms.insert(room);
            }
        }

        cout << roomCnt << '\n';
        for (int room : ans) {
            cout << room << ' ';
        }
        cout << '\n';
    }
}
