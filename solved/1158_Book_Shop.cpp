#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, maxC;
    while (cin >> n >> maxC) {
        vector<int> cost(n), pages(n);
        for (int& c : cost) cin >> c;
        for (int& p : pages) cin >> p;

        vector<int> dpCur(maxC + 1, -INF);
        dpCur[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<int> dpNxt = dpCur;
            for (int c = 0; c + cost[i] <= maxC; c++) {
                if (dpCur[c] >= 0) {
                    dpNxt[c + cost[i]] = max(dpNxt[c + cost[i]], dpCur[c] + pages[i]);
                }
            }
            dpCur.swap(dpNxt);
        }
        cout << *max_element(all(dpCur)) << '\n';
    }
}
