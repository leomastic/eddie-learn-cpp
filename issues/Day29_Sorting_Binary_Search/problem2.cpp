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

int upperBoundIndex(const std::vector<int>& values, int target) {
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int queryCount;
    if (!(std::cin >> n >> queryCount)) return 0;

    std::vector<int> scores(n);
    for (int& score : scores) std::cin >> score;
    std::sort(scores.begin(), scores.end());

    while (queryCount--) {
        int query;
        std::cin >> query;
        std::cout << upperBoundIndex(scores, query) -
                         lowerBoundIndex(scores, query)
                  << '\n';
    }
    return 0;
}
