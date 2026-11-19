#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;

    vector<int> coins(n);
    for (int &coin : coins) {
        cin >> coin;
    }

    const int INF = 1e9;
    vector<int> dp(s + 1, INF);
    dp[0] = 0;

    for (int amount = 1; amount <= s; ++amount) {
        for (int coin : coins) {
            if (coin <= amount) {
                dp[amount] = min(dp[amount], dp[amount - coin] + 1);
            }
        }
    }

    cout << (dp[s] == INF ? -1 : dp[s]) << '\n';
    return 0;
}
