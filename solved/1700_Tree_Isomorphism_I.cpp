#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

void dfs(const int x, const int p, const int height, const vector<vector<int>>& g, vector<int>& h) {
    h[x] = height;
    for (const int y : g[x]) {
        if (y == p) {
            continue;
        }
        dfs(y, x, height + 1, g, h);
    }
}

// graphs are processed together, layer by layer, from the deepest vertices to root
bool areIsomorphic(const vector<vector<vector<int>>>& graphs) {
    assert(sz(graphs) == 2);

    const int n = sz(graphs[0]);
    assert(n == sz(graphs[1]));

    vector<vector<int>> h(2, vector<int>(n)); // [gid][vertex] -> height
    for (int gid = 0; gid < 2; gid++) {
        dfs(0, -1, 0, graphs[gid], h[gid]);
    }

    const int maxH = *max_element(all(h[0]));
    if (maxH != *max_element(all(h[1]))) {
        return false;
    }

    vector<vector<vector<int>>> layers(2, vector<vector<int>>(maxH + 1)); // [gid][height] -> vertices with this height
    for (int gid = 0; gid < 2; gid++) {
        for (int x = 0; x < n; x++) {
            const int height = h[gid][x];
            layers[gid][height].push_back(x);
        }
    }

    vector<vector<int>> label(2, vector<int>(n, -1)); // [gid][vertex] -> label
    vector<vector<vector<int>>> labelsByHeight(2, vector<vector<int>>(maxH + 1)); // [gid][height] -> labels on this height
    for (int height = maxH; height >= 0; height--) {
        vector<pair<vector<int>, ii>> labelSetsWithVertices; // (children labels, (gid, vertex))
        for (int gid = 0; gid < 2; gid++) {
            for (const int x : layers[gid][height]) {
                vector<int> labelSet;
                for (const int y : graphs[gid][x]) {
                    if (h[gid][x] + 1 != h[gid][y]) {
                        continue;
                    }
                    labelSet.push_back(label[gid][y]);
                }
                sort(all(labelSet));
                labelSetsWithVertices.emplace_back(labelSet, ii(gid, x));
            }
        }
        sort(all(labelSetsWithVertices));

        // "compression"
        int curLabel = -1;
        for (int i = 0; i < sz(labelSetsWithVertices); i++) {
            const vector<int>& prevLabelSet = labelSetsWithVertices[i - 1].first;
            const vector<int>& curLabelSet = labelSetsWithVertices[i].first;
            const auto [gid, x] = labelSetsWithVertices[i].second;
            if (i == 0 || prevLabelSet != curLabelSet) {
                curLabel++;
            }
            label[gid][x] = curLabel;
            labelsByHeight[gid][height].push_back(curLabel);
        }
    }

    return labelsByHeight[0] == labelsByHeight[1];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        auto readGraph = [](const int n) {
            vector<vector<int>> g(n);
            for (int i = 0; i < n - 1; i++) {
                int x, y;
                cin >> x >> y;
                x--; y--;
                g[x].push_back(y);
                g[y].push_back(x);
            }
            return g;
        };

        int n;
        cin >> n;
        const vector<vector<int>> g1 = readGraph(n);
        const vector<vector<int>> g2 = readGraph(n);

        const bool ans = areIsomorphic({g1, g2});
        cout << (ans ? "YES" : "NO") << '\n';
    }
}
