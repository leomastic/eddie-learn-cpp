#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long budget;
    if (!(std::cin >> n >> budget)) return 0;

    std::vector<long long> minutes(n);
    for (long long& value : minutes) {
        std::cin >> value;
    }

    int left = 0;
    int best = 0;
    long long sum = 0;

    for (int right = 0; right < n; ++right) {
        sum += minutes[right];
        while (sum > budget) {
            sum -= minutes[left];
            ++left;
        }
        best = std::max(best, right - left + 1);
    }

    std::cout << best << '\n';
    return 0;
}
