#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        long long minutes;
        cin >> minutes;

        long long fee = 5000;
        if (minutes > 30) {
            fee += ((minutes - 30 + 14) / 15) * 2000;
        }
        total += min(fee, 35000LL);
    }

    cout << total << '\n';
    return 0;
}
