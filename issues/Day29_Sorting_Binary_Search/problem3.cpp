#include <algorithm>
#include <iostream>
#include <vector>

int lowerBoundIndex(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size());
    while (left < right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int queryCount;
    if (!(std::cin >> n >> queryCount)) return 0;

    std::vector<int> prices(n);
    for (int& price : prices) std::cin >> price;
    std::sort(prices.begin(), prices.end());

    while (queryCount--) {
        int threshold;
        std::cin >> threshold;
        const int index = lowerBoundIndex(prices, threshold);
        std::cout << (index == n ? -1 : prices[index]) << '\n';
    }
    return 0;
}
