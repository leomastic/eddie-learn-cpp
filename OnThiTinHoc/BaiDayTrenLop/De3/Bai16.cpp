#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string S;
    if (!(std::cin >> S)) return 0;

    std::vector<int> freq(26, 0);
    for (char c : S) {
        freq[c - 'a']++;
    }

    int odd_count = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] % 2 != 0) {
            odd_count++;
        }
    }

    int ans = std::max(0, odd_count - 1);
    std::cout << ans << '\n';

    return 0;
}