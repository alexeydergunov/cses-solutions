#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int LOG = 30;

struct Node {
    array<Node*, 2> link;
};

struct NodePool {
    static const int MAX_NODES = 200000 * LOG;

    int nodeCnt = 0;
    Node nodes[MAX_NODES];

    Node* newNode() {
        assert(nodeCnt < MAX_NODES);
        Node* node = &nodes[nodeCnt++];
        return node;
    }
} NODE_POOL;

void add(Node* root, const int x) {
    Node* curNode = root;
    for (int i = LOG - 1; i >= 0; i--) {
        const int bit = (x >> i) & 1;
        if (curNode->link[bit] == nullptr) {
            curNode->link[bit] = NODE_POOL.newNode();
        }
        curNode = curNode->link[bit];
    }
}

int get(const Node* root, const int x) {
    const Node* curNode = root;
    int result = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        const int bit = (x >> i) & 1;
        if (curNode->link[bit ^ 1] != nullptr) {
            curNode = curNode->link[bit ^ 1];
            result |= 1 << i;
        } else {
            curNode = curNode->link[bit];
        }
        assert(curNode != nullptr);
    }
    return result;
}

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

        Node* root = NODE_POOL.newNode();
        add(root, 0);

        int ans = 0;
        int pref = 0;
        for (int i = 0; i < n; i++) {
            pref ^= a[i];
            const int cand = get(root, pref);
            ans = max(ans, cand);
            add(root, pref);
        }
        cout << ans << '\n';
    }
}
