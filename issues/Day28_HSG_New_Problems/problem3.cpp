#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    int coprimePairs = 0;
    for (int i = 0; i + 1 < n; ++i) {
        if (std::gcd(values[i], values[i + 1]) == 1) ++coprimePairs;
    }

    std::cout << coprimePairs << '\n';
    return 0;
}