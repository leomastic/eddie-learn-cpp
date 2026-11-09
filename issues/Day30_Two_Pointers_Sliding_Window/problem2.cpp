#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int limit;
    if (!(std::cin >> n >> limit)) return 0;

    std::vector<int> categories(n);
    for (int& category : categories) {
        std::cin >> category;
    }

    std::vector<int> frequency(1'000'001, 0);
    int distinct = 0;
    int left = 0;
    int best = 0;

    for (int right = 0; right < n; ++right) {
        if (frequency[categories[right]]++ == 0) {
            ++distinct;
        }
        while (distinct > limit) {
            if (--frequency[categories[left]] == 0) {
                --distinct;
            }
            ++left;
        }
        best = std::max(best, right - left + 1);
    }

    std::cout << best << '\n';
    return 0;
}
