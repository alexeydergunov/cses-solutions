#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct MedianFinder {
    multiset<ll> small;
    multiset<ll> large;
    ll sumSmall = 0;
    ll sumLarge = 0;

    void balance() {
        const int n = sz(small) + sz(large);

        while (sz(small) > (n + 1) / 2) {
            auto itS = --small.end();
            const ll x = *itS;
            large.insert(x);
            small.erase(itS);
            sumLarge += x;
            sumSmall -= x;
        }
        while (sz(large) > n / 2) {
            auto itL = large.begin();
            const ll x = *itL;
            small.insert(x);
            large.erase(itL);
            sumSmall += x;
            sumLarge -= x;
        }

        assert(sz(small) == (n + 1) / 2);
        assert(sz(large) == n / 2);
        if (!small.empty() && !large.empty()) {
            assert(*small.rbegin() <= *large.begin());
        }
    }

    void add(const ll x) {
        if (small.empty() || x <= *small.rbegin()) {
            small.insert(x);
            sumSmall += x;
        } else {
            large.insert(x);
            sumLarge += x;
        }
        balance();
    }

    void remove(const ll x) {
        auto itS = small.find(x);
        if (itS != small.end()) {
            small.erase(itS);
            sumSmall -= x;
        } else {
            auto itL = large.find(x);
            assert(itL != large.end());
            large.erase(itL);
            sumLarge -= x;
        }
        balance();
    }

    ll getCost() {
        const ll median = *small.rbegin();
        ll ans = 0;
        ans += median * sz(small) - sumSmall;
        ans += sumLarge - median * sz(large);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, k;
    while (cin >> n >> k) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        MedianFinder mf;
        for (int i = 0; i < k; i++) {
            mf.add(a[i]);
        }

        cout << mf.getCost();
        for (int i = k; i < n; i++) {
            mf.remove(a[i - k]);
            mf.add(a[i]);
            cout << ' ' << mf.getCost();
        }
        cout << '\n';
    }
}
