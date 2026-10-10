#include <bits/stdc++.h>

void solve() {
    long long n;
    if (!(std::cin >> n)) return;

    std::vector<long long> sequence;
    long long max_val = n;

    sequence.push_back(n);
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        sequence.push_back(n);
        if (n > max_val) {
            max_val = n;
        }
    }

    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << (i + 1 == sequence.size() ? "" : " ");
    }
    std::cout << "\n";

    std::cout << sequence.size() - 1 << "\n";

    std::cout << max_val << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}