#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long a, b, n;
    if (!(std::cin >> a >> b >> n)) return 0;

    long long remain = a % b;
    int presentNumber = 0;

    for (int i = 0; i < n; ++i) {
        remain *= 10;
        presentNumber = remain / b;
        remain %= b;
    }

    std::cout << presentNumber << "\n";

    return 0;
}