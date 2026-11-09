#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long target;
    if (!(std::cin >> n >> target)) return 0;

    std::vector<long long> values(n);
    for (long long& value : values) {
        std::cin >> value;
    }

    int left = 0;
    int best = n + 1;
    long long sum = 0;

    for (int right = 0; right < n; ++right) {
        sum += values[right];
        while (sum >= target) {
            best = std::min(best, right - left + 1);
            sum -= values[left];
            ++left;
        }
    }

    std::cout << (best == n + 1 ? 0 : best) << '\n';
    return 0;
}
