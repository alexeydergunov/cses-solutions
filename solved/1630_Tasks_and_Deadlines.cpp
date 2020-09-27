#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Task {
    ll duration, deadline;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<Task> tasks(n);
        for (auto& t : tasks) {
            cin >> t.duration >> t.deadline;
        }

        // exchange argument
        // simplified comparator is (t1.duration < t2.duration)
        auto getCost = [](const Task& t1, const Task& t2) {
            ll ans = 0;
            ans += t1.deadline - t1.duration;
            ans += t2.deadline - (t1.duration + t2.duration);
            return ans;
        };
        sort(all(tasks), [&](const Task& t1, const Task& t2) {
            return getCost(t1, t2) > getCost(t2, t1);
        });

        ll ans = 0;
        ll curT = 0;
        for (const Task& t : tasks) {
            curT += t.duration;
            ans += t.deadline - curT;
        }
        cout << ans << '\n';
    }
}
