#include <bits/stdc++.h>

void solve() {
    long long a, b, c, d;
    if (!(std::cin >> a >> b >> c >> d)) return;

    long long x = a * d - c * b;
    long long y = b * d;

    long long g = std::gcd(x, y);
    x /= g;
    y /= g;

    if (x == 0) {
        y = 1;
    } else if (y < 0) {
        x = -x;
        y = -y;
    }

    std::cout << x << "/" << y << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}