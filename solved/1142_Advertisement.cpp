#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct SparseTable {
    int n, logN;
    vector<vector<pair<ll, int>>> t; // (value, index)

    SparseTable(const vector<ll>& a) {
        n = sz(a);
        logN = 0;
        while ((1 << logN) <= n) {
            logN++;
        }

        t.resize(logN);
        for (int z = 0; z < logN; z++) {
            t[z].resize(n - (1 << z) + 1);
            assert(sz(t[z]) > 0);
        }

        for (int i = 0; i < n; i++) {
            t[0][i] = {a[i], i};
        }
        for (int z = 1; z < logN; z++) {
            for (int i = 0; i < sz(t[z]); i++) {
                const auto& val1 = t[z - 1][i];
                const auto& val2 = t[z - 1][i + (1 << (z - 1))];
                t[z][i] = min(val1, val2);
            }
        }
    }

    pair<ll, int> getMin(const int L, const int R) {
        const int len = R - L + 1;
        assert(len > 0);
        const int z = 31 - __builtin_clz(len);
        assert(0 <= z && z < logN);
        assert(2 * (1 << z) >= len);
        const auto& val1 = t[z][L];
        const auto& val2 = t[z][R - (1 << z) + 1];
        return min(val1, val2);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        SparseTable t(a);
        ll ans = 0;
        function<void(int,int)> rec = [&](const int L, const int R) {
            if (L > R) {
                return;
            }
            const auto [minVal, minIndex] = t.getMin(L, R);
            ans = max(ans, minVal * (R - L + 1));
            rec(L, minIndex - 1);
            rec(minIndex + 1, R);
        };
        rec(0, n - 1);

        cout << ans << '\n';
    }
}
