#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    int ans_l = 1, ans_r = 1, max_len = 1;
    int cur_l = 1, cur_len = 1;

    for (int i = 2; i <= n; ++i) {
        if (abs(a[i]) % 2 == abs(a[i - 1]) % 2) {
            cur_len++;
        } else {
            cur_l = i;
            cur_len = 1;
        }

        if (cur_len > max_len) {
            max_len = cur_len;
            ans_l = cur_l;
            ans_r = i;
        }
    }

    std::cout << ans_l << " " << ans_r << " " << max_len << "\n";

    return 0;
}