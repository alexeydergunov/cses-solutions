#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

struct Segment {
    int L, R;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, k;
    while (cin >> n >> k) {
        vector<Segment> segments(n);
        for (auto& s : segments) {
            cin >> s.L >> s.R;
        }
        sort(all(segments), [](const Segment& e1, const Segment& e2) {
            return e1.R < e2.R;
        });

        set<ii> used; // (finish time, id)
        for (int i = 0; i < k; i++) {
            used.insert({0, i});
        }
        int ans = 0;
        for (const auto& s : segments) {
            auto it = used.upper_bound({s.L, INF});
            if (it == used.begin()) {
                continue;
            }
            it--;
            // found a man who ends his current movie as close as possible to s.L
            assert(it->first <= s.L);
            const int id = it->second;
            used.erase(it);
            used.insert({s.R, id});
            ans++;
        }
        cout << ans << '\n';
    }
}
