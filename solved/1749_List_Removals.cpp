#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct FenwickTree {
    int n;
    vector<int> t;

    FenwickTree(int n_) {
        n = n_;
        t.resize(n + 1);
    }

    void inc(int pos, const int delta) { // 1-indexed
        assert(1 <= pos && pos <= n);
        while (pos <= n) {
            t[pos] += delta;
            pos += pos & -pos;
        }
    }

    int lowerBoundIndex(const int needSum) {
        int step = 1 << 18;
        int index = 0;
        int curSum = 0;
        while (step > 0) {
            if (index + step <= n && curSum + t[index + step] < needSum) {
                curSum += t[index + step];
                index += step;
            }
            step /= 2;
        }
        return index + 1; // 1-indexed
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        FenwickTree t(n); // 1-indexed
        for (int i = 1; i <= n; i++) {
            t.inc(i, 1);
        }

        for (int i = 0; i < n; i++) {
            int s;
            cin >> s;
            assert(1 <= s && s <= n - i);
            int index = t.lowerBoundIndex(s);
            assert(1 <= index && index <= n);
            t.inc(index, -1);
            cout << a[index - 1] << ' ';
        }
        cout << '\n';
    }
}
