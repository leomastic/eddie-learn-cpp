#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int MAX = 1000000;

    std::vector<bool> isPrime(MAX + 1, true);

    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= MAX; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int n;
    std::cin >> n;

    while (n--) {
        long long x;
        std::cin >> x;

        long long root = std::sqrt(x);

        if (root * root == x && isPrime[root]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}