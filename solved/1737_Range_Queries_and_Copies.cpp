#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

struct Node {
    ll sum;
    int L, R; // index range
    const Node* left;
    const Node* right;
};

struct NodePool {
    static const int NODE_POOL_SIZE = 400000 * 18; // should be enough in this problem

    int nodeCnt = 0;
    Node pool[NODE_POOL_SIZE];

    Node* newNode(const ll sum, const int L, const int R, const Node* left, const Node* right) {
        assert(nodeCnt < NODE_POOL_SIZE);
        Node* node = &pool[nodeCnt++];
        node->sum = sum;
        node->L = L;
        node->R = R;
        node->left = left;
        node->right = right;
        return node;
    }
} NODE_POOL;

const Node* build(const vector<ll>& a, const int l, const int r) {
    if (l == r) {
        return NODE_POOL.newNode(a[l], l, r, nullptr, nullptr);
    }
    const int m = (l + r) / 2;
    const Node* left = build(a, l, m);
    const Node* right = build(a, m + 1, r);
    return NODE_POOL.newNode(left->sum + right->sum, l, r, left, right);
}

const Node* build(const vector<ll>& a) {
    return build(a, 0, sz(a) - 1);
}

ll getSum(const Node* node, const int needL, const int needR) {
    assert(node != nullptr);
    const int l = node->L;
    const int r = node->R;
    assert(l <= needL && needR <= r);
    if (l == needL && r == needR) {
        return node->sum;
    }
    const int m = (l + r) / 2;
    if (needR <= m) {
        return getSum(node->left, needL, needR);
    }
    if (m + 1 <= needL) {
        return getSum(node->right, needL, needR);
    }
    const ll sum1 = getSum(node->left, needL, m);
    const ll sum2 = getSum(node->right, m + 1, needR);
    return sum1 + sum2;
}

const Node* setValue(const Node* node, const int pos, const ll value) {
    assert(node != nullptr);
    const int l = node->L;
    const int r = node->R;
    if (l == r) {
        assert(node->left == nullptr);
        assert(node->right == nullptr);
        assert(pos == l);
        return NODE_POOL.newNode(value, l, r, nullptr, nullptr);
    }
    int m = (l + r) / 2;
    if (pos <= m) {
        const Node* newLeft = setValue(node->left, pos, value);
        return NODE_POOL.newNode(newLeft->sum + node->right->sum, l, r, newLeft, node->right);
    } else {
        const Node* newRight = setValue(node->right, pos, value);
        return NODE_POOL.newNode(node->left->sum + newRight->sum, l, r, node->left, newRight);
    }
}

const Node* clone(const Node* node) {
    return NODE_POOL.newNode(node->sum, node->L, node->R, node->left, node->right);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, Q;
    while (cin >> n >> Q) {
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<const Node*> roots = {build(a)};
        for (int q = 1; q <= Q; q++) {
            int type, id;
            cin >> type >> id;
            id--;
            assert(0 <= id && id < sz(roots));
            if (type == 1) {
                int pos;
                ll value;
                cin >> pos >> value;
                pos--;
                roots[id] = setValue(roots[id], pos, value);
            } else if (type == 2) {
                int L, R;
                cin >> L >> R;
                L--; R--;
                cout << getSum(roots[id], L, R) << '\n';
            } else {
                const Node* newRoot = clone(roots[id]);
                roots.push_back(newRoot);
            }
        }
    }
}
