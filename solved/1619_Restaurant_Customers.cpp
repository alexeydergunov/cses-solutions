#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Event {
    int x, type;
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
            int a, b;
            cin >> a >> b;
            events.push_back(Event{a, 0});
            events.push_back(Event{b, 1});
        }
        sort(all(events), [](const Event& e1, const Event& e2) {
            if (e1.x != e2.x) return e1.x < e2.x;
            return e1.type < e2.type;
        });

        int ans = 0;
        int now = 0;
        for (const Event& e : events) {
            if (e.type == 0) {
                now++;
            } else {
                now--;
            }
            assert(now >= 0);
            ans = max(ans, now);
        }
        cout << ans << '\n';
    }
}
