#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct MedianFinder {
    multiset<int> small;
    multiset<int> large;

    void balance() {
        const int n = sz(small) + sz(large);

        while (sz(small) > (n + 1) / 2) {
            auto itS = --small.end();
            large.insert(*itS);
            small.erase(itS);
        }
        while (sz(large) > n / 2) {
            auto itL = large.begin();
            small.insert(*itL);
            large.erase(itL);
        }

        assert(sz(small) == (n + 1) / 2);
        assert(sz(large) == n / 2);
        if (!small.empty() && !large.empty()) {
            assert(*small.rbegin() <= *large.begin());
        }
    }

    void add(const int x) {
        if (small.empty() || x <= *small.rbegin()) {
            small.insert(x);
        } else {
            large.insert(x);
        }
        balance();
    }

    void remove(const int x) {
        auto itS = small.find(x);
        if (itS != small.end()) {
            small.erase(itS);
        } else {
            auto itL = large.find(x);
            assert(itL != large.end());
            large.erase(itL);
        }
        balance();
    }

    int get() {
        return *small.rbegin();
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        MedianFinder mf;
        for (int i = 0; i < k; i++) {
            mf.add(a[i]);
        }

        cout << mf.get();
        for (int i = k; i < n; i++) {
            mf.remove(a[i - k]);
            mf.add(a[i]);
            cout << ' ' << mf.get();
        }
        cout << '\n';
    }
}
