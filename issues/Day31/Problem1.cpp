#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    long long tot = 0;

    for (int i = 0; i < n; ++i) {
        long long t;
        cin >> t;

        long long fee = 0;

        if (t <= 30) {
            fee = 5000;
        } else {
            long long rem = t - 30;
            long long blk = (rem + 14) / 15;
            fee = 5000 + blk * 2000;
        }

        fee = min(fee, 35000LL);
        tot += fee;
    }

    cout << tot << '\n';

    return 0;
}