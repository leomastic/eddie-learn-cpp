#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        long long usage;
        cin >> usage;

        long long bill = min(usage, 50LL) * 1000;
        if (usage > 50) {
            bill += min(usage - 50, 100LL) * 1500;
        }
        if (usage > 150) {
            bill += (usage - 150) * 2000;
        }
        if (usage > 200) {
            bill += bill / 10;
        }

        total += bill;
    }

    cout << total << '\n';
    return 0;
}
