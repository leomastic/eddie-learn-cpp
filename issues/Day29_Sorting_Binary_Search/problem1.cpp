#include <algorithm>
#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;
    while (left <= right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] == target) return middle;
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int queryCount;
    if (!(std::cin >> n >> queryCount)) return 0;

    std::vector<int> codes(n);
    for (int& code : codes) std::cin >> code;
    std::sort(codes.begin(), codes.end());

    while (queryCount--) {
        int query;
        std::cin >> query;
        std::cout << (binarySearch(codes, query) >= 0 ? "YES" : "NO") << '\n';
    }
    return 0;
}
