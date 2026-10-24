#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> values(n);
    int maximum = 1;
    for (int& value : values) {
        std::cin >> value;
        if (value > maximum) maximum = value;
    }

    std::vector<int> smallestPrimeFactor(maximum + 1);
    for (int i = 2; i <= maximum; ++i) {
        if (smallestPrimeFactor[i] != 0) continue;
        smallestPrimeFactor[i] = i;
        if (i <= maximum / i) {
            for (int multiple = i * i; multiple <= maximum; multiple += i) {
                if (smallestPrimeFactor[multiple] == 0) {
                    smallestPrimeFactor[multiple] = i;
                }
            }
        }
    }

    for (int index = 0; index < n; ++index) {
        int value = values[index];
        int signature = 0;
        while (value > 1) {
            const int prime = smallestPrimeFactor[value];
            ++signature;
            while (value % prime == 0) value /= prime;
        }

        if (index > 0) std::cout << ' ';
        std::cout << signature;
    }
    std::cout << '\n';
    return 0;
}
