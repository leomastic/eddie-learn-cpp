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

    int squareFreeCount = 0;
    for (int value : values) {
        bool squareFree = true;
        while (value > 1) {
            const int prime = smallestPrimeFactor[value];
            value /= prime;
            if (value % prime == 0) {
                squareFree = false;
                break;
            }
        }
        if (squareFree) ++squareFreeCount;
    }

    std::cout << squareFreeCount << '\n';
    return 0;
}