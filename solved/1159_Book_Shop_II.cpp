#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)((v).size()))
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;

const int INF = int(1e9);

struct Book {
    int cost, pages, cnt;
};

vector<Book> normalize(const vector<Book>& books) {
    vector<Book> newBooks;
    for (const Book& b : books) {
        // for each book, make log(cnt) copies instead of cnt copies
        vector<int> newCnts;
        int now = 1;
        int rem = b.cnt;
        while (true) {
            if (now > rem) {
                break;
            }
            newCnts.push_back(now);
            rem -= now;
            now *= 2;
        }
        if (rem > 0) {
            newCnts.push_back(rem);
        }
        assert(accumulate(all(newCnts), 0) == b.cnt);
        for (const int cnt : newCnts) {
            newBooks.push_back(Book{b.cost, b.pages, cnt});
        }
    }
    return newBooks;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cout.precision(15); cout.setf(ios::fixed);
    cerr.precision(15); cerr.setf(ios::fixed);

    int n, maxCost;
    while (cin >> n >> maxCost) {
        vector<Book> books(n);
        for (Book& b : books) cin >> b.cost;
        for (Book& b : books) cin >> b.pages;
        for (Book& b : books) cin >> b.cnt;

        books = normalize(books);

        vector<int> dpCur(maxCost + 1, -INF);
        dpCur[0] = 0;
        for (const Book& b : books) {
            vector<int> dpNext = dpCur;
            const int addCost = b.cost * b.cnt;
            const int addPages = b.pages * b.cnt;
            for (int c = 0; c + addCost <= maxCost; c++) {
                dpNext[c + addCost] = max(dpNext[c + addCost], dpCur[c] + addPages);
            }
            dpCur.swap(dpNext);
        }
        cout << *max_element(all(dpCur)) << '\n';
    }
}
