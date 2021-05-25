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

    void inc(int pos, int delta) {
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

    int upperBoundIndex(int needSum) {
        int step = 1 << 18;
        int i = 0;
        int curSum = 0;
        while (step > 0) {
            if (i + step <= n && curSum + t[i + step] <= needSum) {
                curSum += t[i + step];
                i += step;
            }
            step /= 2;
        }
        return i;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, k;
    while (cin >> n >> k) {
        FenwickTree t(n);
        for (int i = 0; i < n; i++) {
            t.inc(i, 1);
        }

        vector<int> ans;
        int lastPos = -1;
        for (int i = 0; i < n; i++) {
            int leftSum = t.sum(lastPos);
            int rightSum = (n - i) - leftSum;
            int order = k % (n - i);
            int pos;
            if (order < rightSum) {
                pos = t.upperBoundIndex(leftSum + order);
            } else {
                order -= rightSum;
                pos = t.upperBoundIndex(order);
            }
            ans.push_back(pos);
            t.inc(pos, -1);
            lastPos = pos;
        }

        for (int x : ans) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}
