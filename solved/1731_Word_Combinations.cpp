#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const ll MOD = ll(1e9) + 7;

struct Node {
    int cnt;
    vector<Node*> link;
};

struct NodePool {
    static const int MAX_NODES = 2000000; // should be enough in this problem

    int nodeCnt = 0;
    Node nodes[MAX_NODES];

    Node* newNode() {
        assert(nodeCnt < MAX_NODES);
        Node* node = &nodes[nodeCnt++];
        node->cnt = 0;
        node->link.resize(26);
        return node;
    }
} NODE_POOL;

void addString(Node* node, const string& s, const int pos) {
    assert(node != nullptr);
    if (pos == sz(s)) {
        node->cnt++;
        return;
    }
    const char c = s[pos];
    Node*& next = node->link[c - 'a'];
    if (next == nullptr) {
        next = NODE_POOL.newNode();
    }
    addString(next, s, pos + 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    string s;
    while (cin >> s) {
        Node* root = NODE_POOL.newNode();
        int k;
        cin >> k;
        while (k--) {
            string word;
            cin >> word;
            addString(root, word, 0);
        }

        const int n = sz(s);
        vector<ll> dp(n + 1);
        dp[0] = 1;

        function<void(const Node*,int,int)> dfs = [&](const Node* node, const int start, const int depth) {
            assert(start + depth <= n);
            if (node == nullptr) {
                return;
            }
            const int cnt = node->cnt;
            if (cnt > 0) {
                dp[start + depth] += ll(cnt) * dp[start];
                dp[start + depth] %= MOD;
            }
            if (start + depth == n) {
                return;
            }
            const char c = s[start + depth];
            dfs(node->link[c - 'a'], start, depth + 1);
        };

        for (int i = 0; i < n; i++) {
            dfs(root, i, 0);
        }
        cout << dp[n] << '\n';
    }
}
