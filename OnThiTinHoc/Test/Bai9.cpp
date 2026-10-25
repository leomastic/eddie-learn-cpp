#include <bits/stdc++.h>

using namespace std;

long long reverseNum(long long m) {
    long long rev = 0;
    while (m > 0) {
        rev = rev * 10 + m % 10;
        m /= 10;
    }
    return rev;
}

void solve() {
    long long k;
    if (!(cin >> k)) return;

    int count = 0;
    for (long long m = 1; m <= k; ++m) {
        long long n = reverseNum(m);
        if (gcd(m, n) == 1) {
            count++;
        }
    }

    cout << count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}