#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    long long W = 0;
    for (int i = 1; i <= n; ++i) {
        long long a;
        std::cin >> a;
        W += i * a;
    }

    std::cout << W << "\n";
    return 0;
}