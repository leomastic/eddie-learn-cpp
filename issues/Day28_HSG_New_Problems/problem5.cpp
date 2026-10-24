#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int queryCount;
    if (!(std::cin >> n >> queryCount)) return 0;

    std::vector<int> values(n);
    int maximum = 1;
    for (int& value : values) {
        std::cin >> value;
        if (value > maximum) maximum = value;
    }

    std::vector<bool> isPrime(maximum + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int prime = 2; prime <= maximum / prime; ++prime) {
        if (!isPrime[prime]) continue;
        for (int multiple = prime * prime; multiple <= maximum; multiple += prime) {
            isPrime[multiple] = false;
        }
    }

    std::vector<int> nonPrimePrefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        nonPrimePrefix[i + 1] =
            nonPrimePrefix[i] + (isPrime[values[i]] ? 0 : 1);
    }

    while (queryCount--) {
        int left;
        int right;
        std::cin >> left >> right;
        std::cout << nonPrimePrefix[right] - nonPrimePrefix[left - 1] << '\n';
    }

    return 0;
}