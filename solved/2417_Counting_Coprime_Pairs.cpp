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
        vector<int> a(n);
        for (int& x : a) {
            cin >> x;
        }
        const int maxX = *max_element(all(a));

        vector<int> smallestPrime(maxX + 1, -1);
        for (int i = 2; i <= maxX; i++) {
            if (smallestPrime[i] == -1) {
                smallestPrime[i] = i;
                if (ll(i) * i <= maxX) {
                    for (int j = i * i; j <= maxX; j += i) {
                        if (smallestPrime[j] == -1) {
                            smallestPrime[j] = i;
                        }
                    }
                }
            }
        }

        // we are interested only in divisors that consist of all different primes
        vector<vector<ii>> divisors(maxX + 1); // (divisor, number of primes)
        for (int i = 2; i <= maxX; i++) {
            int x = i;
            vector<int> primes;
            while (x > 1) {
                const int p = smallestPrime[x];
                assert(p != 1);
                primes.push_back(p);
                x /= p;
            }
            sort(all(primes));
            primes.resize(unique(all(primes)) - primes.begin());

            for (int mask = 1; mask < (1 << sz(primes)); mask++) {
                int d = 1;
                int bc = 0;
                for (int bit = 0; bit < sz(primes); bit++) {
                    if (mask & (1 << bit)) {
                        d *= primes[bit];
                        bc++;
                    }
                }
                divisors[i].emplace_back(d, bc);
            }
        }

        vector<int> cnt(maxX + 1);
        ll ans = 0;
        for (const int x : a) {
            for (const auto [d, bc] : divisors[x]) {
                if (bc % 2 != 0) {
                    ans += cnt[d];
                } else {
                    ans -= cnt[d];
                }
                cnt[d]++;
            }
        }
        cout << ll(n) * (n - 1) / 2 - ans << '\n';
    }
}
