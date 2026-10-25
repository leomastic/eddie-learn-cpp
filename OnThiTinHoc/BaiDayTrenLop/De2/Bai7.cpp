#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long x, y;
    if (!(std::cin >> x >> y)) return 0;

    long long a = std::gcd(x, y);

    long long countSquares = (x / a) * (y / a);

    std::cout << countSquares << "\n";

    return 0;
}