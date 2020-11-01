#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n;
    while (cin >> n) {
        vector<int> preorder(n);
        vector<int> inorder(n);
        for (int i = 0; i < n; i++) {
            cin >> preorder[i];
            preorder[i]--;
        }
        for (int i = 0; i < n; i++) {
            cin >> inorder[i];
            inorder[i]--;
        }

        vector<int> inorderPos(n);
        for (int i = 0; i < n; i++) {
            inorderPos[inorder[i]] = i;
        }

        vector<int> postorder;
        function<void(int,int)> rec = [&](const int L, const int R) { // [L, R)
            assert(L <= R);
            if (L == R) {
                return;
            }
            const int root = preorder[L];
            int mid = L + 1;
            while (mid < R && inorderPos[preorder[mid]] < inorderPos[root]) {
                mid++;
            }
            rec(L + 1, mid);
            rec(mid, R);
            postorder.push_back(root);
        };
        rec(0, n);
        assert(sz(postorder) == n);

        for (const int val : postorder) {
            cout << val + 1 << ' ';
        }
        cout << '\n';
    }
}
