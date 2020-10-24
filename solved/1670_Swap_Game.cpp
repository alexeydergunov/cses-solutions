#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);
const int FACT_9 = 362880;

const vector<ii> swaps = {
    {0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8},
    {0, 3}, {3, 6}, {1, 4}, {4, 7}, {2, 5}, {5, 8},
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    // precalc begin
    auto pt1 = chrono::high_resolution_clock::now();

    vector<int> pow10(10);
    pow10[0] = 1;
    for (int i = 1; i < 10; i++) {
        pow10[i] = pow10[i - 1] * 10;
    }

    vector<int> stateToNum(FACT_9 + 1); // 1-indexed
    unordered_map<int, int> numToState(FACT_9 * 3 + 1);
    {
        vector<int> tmpVec(9);
        iota(all(tmpVec), 1);
        int index = 0;
        do {
            index++;
            int num = 0;
            for (int x : tmpVec) {
                num = num * 10 + x;
            }
            stateToNum[index] = num;
            numToState[num] = index;
        } while (next_permutation(all(tmpVec)));
        assert(index == FACT_9);
        assert(sz(numToState) == FACT_9);
    }

    auto pt2 = chrono::high_resolution_clock::now();
    auto precalcTime = chrono::duration_cast<chrono::milliseconds>(pt2 - pt1).count();
    cerr << "Total precalc time: " << precalcTime << " ms" << endl;
    // precalc end

    // solve function begin
    auto solveTest = [&](const int startNum) {
        const int finishNum = 123456789;

        const int start = numToState[startNum];
        const int finish = numToState[finishNum];
        assert(start > 0);
        assert(finish > 0);

        queue<int> q;
        vector<int> dist(FACT_9 + 1, INF); // 1-indexed
        dist[start] = 0;
        q.push(start);
        auto relax = [&](const int x, const int y) {
            if (dist[y] > dist[x] + 1) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        };

        auto getDigit = [&](int x, const int i) {
            x %= pow10[i + 1];
            if (x > 0) x /= pow10[i];
            return x;
        };
        auto swapDigits = [&](int x, const int i, const int j) {
            const int di = getDigit(x, i);
            const int dj = getDigit(x, j);
            assert(di != 0);
            assert(dj != 0);
            x -= di * pow10[i];
            x += dj * pow10[i];
            x -= dj * pow10[j];
            x += di * pow10[j];
            return x;
        };

        while (!q.empty()) {
            const int x = q.front(); q.pop();
            assert(dist[x] < INF);
            if (x == finish) {
                break;
            }
            const int curNum = stateToNum[x];
            for (const auto [i, j] : swaps) {
                const int nextNum = swapDigits(curNum, i, j);
                const int y = numToState[nextNum];
                assert(y > 0);
                relax(x, y);
            }
        }

        cout << dist[finish] << '\n';
    };
    // solve function end

    int startNum;
    while (cin >> startNum) {
        for (int i = 1; i < 9; i++) {
            int x;
            cin >> x;
            startNum = startNum * 10 + x;
        }
        auto tt1 = chrono::high_resolution_clock::now();
        solveTest(startNum);
        auto tt2 = chrono::high_resolution_clock::now();
        auto testTime = chrono::duration_cast<chrono::milliseconds>(tt2 - tt1).count();
        cerr << "Total test time for " << startNum << ": " << testTime << " ms" << endl;
    }
}
