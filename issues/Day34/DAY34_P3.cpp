#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> divisorCount(n + 1, 0);
    for (int d = 1; d <= n; ++d) {
        for (int x = d; x <= n; x += d) {
            ++divisorCount[x];
        }
    }

    int best = 1;
    for (int x = 2; x <= n; ++x) {
        if (divisorCount[x] > divisorCount[best]) {
            best = x;
        }
    }

    cout << best << ' ' << divisorCount[best] << '\n';
    return 0;
}
