#include <deque>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long limit;
    if (!(std::cin >> n >> limit)) return 0;

    std::vector<int> values(n);
    for (int& value : values) {
        std::cin >> value;
    }

    std::deque<int> minimums;
    std::deque<int> maximums;
    int left = 0;
    long long count = 0;

    for (int right = 0; right < n; ++right) {
        while (!minimums.empty() &&
               values[minimums.back()] >= values[right]) {
            minimums.pop_back();
        }
        minimums.push_back(right);

        while (!maximums.empty() &&
               values[maximums.back()] <= values[right]) {
            maximums.pop_back();
        }
        maximums.push_back(right);

        while (static_cast<long long>(values[maximums.front()]) -
                   values[minimums.front()] >
               limit) {
            if (minimums.front() == left) {
                minimums.pop_front();
            }
            if (maximums.front() == left) {
                maximums.pop_front();
            }
            ++left;
        }

        count += right - left + 1;
    }

    std::cout << count << '\n';
    return 0;
}
