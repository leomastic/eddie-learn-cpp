#include <bits/stdc++.h>

void print128(__int128 n) {
    if (n == 0) {
        std::cout << 0 << std::endl;
        return;
    }
    if (n < 0) {
        std::cout << "-";
        n = -n;
    }
    std::string s;
    while (n > 0) {
        s += '0' + (n % 10);
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int64_t a, b, c, M;
    constexpr int64_t max_val = 1000000000000000000LL;
    constexpr int64_t min_val = -max_val;
    constexpr int64_t max_modulus = 10000000000LL;

    if (!(std::cin >> a >> b >> c >> M)) {
        std::cerr << "Error: expected a, b, c, and M.\n";
        return 1;
    }
    if (a < min_val || a > max_val ||
        b < min_val || b > max_val ||
        c < min_val || c > max_val) {
        std::cerr << "Error: a, b, and c must be between -10^18 and 10^18.\n";
        return 1;
    }
    if (M < 1 || M > max_modulus) {
        std::cerr << "Error: M must be between 1 and 10^10.\n";
        return 1;
    }

    const __int128 ab = static_cast<__int128>(a) * b;
    const __int128 ac = static_cast<__int128>(a) * c;
    const __int128 bc = static_cast<__int128>(b) * c;
    const __int128 maxProduct = std::max({ab, ac, bc});
    const __int128 ans = maxProduct % M;

    print128(ans);

    return 0;
}