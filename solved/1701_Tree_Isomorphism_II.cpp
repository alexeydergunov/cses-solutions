#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

void dfs(const int x, const int p, const int height, const vector<vector<int>>& g, vector<int>& h, vector<int>& parent) {
    h[x] = height;
    if (!parent.empty()) { // nullable
        parent[x] = p;
    }
    for (const int y : g[x]) {
        if (y == p) {
            continue;
        }
        dfs(y, x, height + 1, g, h, parent);
    }
}

// graphs are processed together, layer by layer, from the deepest vertices to root
bool areIsomorphic(const vector<vector<vector<int>>>& graphs, const vector<int>& roots) {
    assert(sz(graphs) == 2);
    assert(sz(roots) == 2);

    const int n = sz(graphs[0]);
    assert(n == sz(graphs[1]));

    vector<vector<int>> h(2, vector<int>(n)); // [gid][vertex] -> height
    for (int gid = 0; gid < 2; gid++) {
        vector<int> unused;
        dfs(roots[gid], -1, 0, graphs[gid], h[gid], unused);
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

vector<int> findCenters(const vector<vector<int>>& g) {
    const int n = sz(g);

    vector<int> dist(n);
    vector<int> parent;
    dfs(0, -1, 0, g, dist, parent); // parent is unused here
    const int end1 = int(max_element(all(dist)) - dist.begin());

    dist.assign(n, 0);
    parent.assign(n, -1);
    dfs(end1, -1, 0, g, dist, parent);
    const int end2 = int(max_element(all(dist)) - dist.begin());

    vector<int> path;
    for (int x = end2; x != -1; x = parent[x]) {
        path.push_back(x);
    }
    assert(path.back() == end1);

    if (sz(path) % 2 != 0) {
        return {path[sz(path) / 2]};
    } else {
        return {path[sz(path) / 2 - 1], path[sz(path) / 2]};
    }
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

        vector<int> centers1 = findCenters(g1);
        vector<int> centers2 = findCenters(g2);

        bool ans = false;
        for (int c1 : centers1) {
            for (const int c2 : centers2) {
                if (areIsomorphic({g1, g2}, {c1, c2})) {
                    ans = true;
                    break;
                }
            }
            if (ans) break;
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
}
