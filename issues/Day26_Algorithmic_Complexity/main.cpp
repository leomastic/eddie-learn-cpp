#include <bits/stdc++.h>

long long linearWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        ++operations;
    }

    return operations;
}

long long quadraticWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++operations;
        }
    }

    return operations;
}

int countEqualPairs(const std::vector<int>& a) {
    int count = 0;
    const int n = static_cast<int>(a.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::cout << countEqualPairs(a) << '\n';

    return 0;
}