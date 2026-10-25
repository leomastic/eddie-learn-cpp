#include <algorithm>
#include <iostream>
#include <vector>

int upperBoundIndex(const std::vector<long long>& values, long long target) {
    int left = 0;
    int right = static_cast<int>(values.size());
    while (left < right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

long long countPairsUnderLimit(std::vector<long long>& values,
                               long long limit) {
    std::sort(values.begin(), values.end());

    long long pairCount = 0;
    for (int i = 0; i < static_cast<int>(values.size()) - 1; ++i) {
        const long long largestPartner = limit - values[i];
        const int end = upperBoundIndex(values, largestPartner);
        const int firstEligible = i + 1;
        if (end > firstEligible) {
            pairCount += end - firstEligible;
        }
    }
    return pairCount;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long limit;
    if (!(std::cin >> n >> limit)) return 0;

    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;
    std::cout << countPairsUnderLimit(values, limit) << '\n';
    return 0;
}
