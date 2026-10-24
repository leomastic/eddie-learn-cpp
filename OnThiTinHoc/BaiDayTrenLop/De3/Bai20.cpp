#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::unordered_set<int> unique_elements;
    for (int i = 0; i < n; ++i) {
        int test;
        std::cin >> test;
        unique_elements.insert(test);
    }

    std::cout << unique_elements.size() << "\n";

    return 0;
}