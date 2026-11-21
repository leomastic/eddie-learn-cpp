#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    if (!(cin >> n >> s)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<int> dp(s + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int sum = c[i]; sum <= s; ++sum) {
            dp[sum] += dp[sum - c[i]];
            if (dp[sum] >= MOD) dp[sum] -= MOD;
        }
    }

    cout << dp[s] << '\n';
    return 0;
}