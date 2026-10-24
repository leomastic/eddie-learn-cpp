#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int left;
    int right;
    if (!(std::cin >> left >> right)) return 0;

    std::vector<int> divisorCount(right + 1, 0);
    for (int divisor = 1; divisor <= right; ++divisor) {
        for (int multiple = divisor; multiple <= right; multiple += divisor) {
            ++divisorCount[multiple];
        }
    }

    int champion = left;
    for (int value = left + 1; value <= right; ++value) {
        if (divisorCount[value] > divisorCount[champion]) {
            champion = value;
        }
    }

    std::cout << champion << ' ' << divisorCount[champion] << '\n';
    return 0;
}