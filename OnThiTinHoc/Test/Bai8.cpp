#include <bits/stdc++.h>

bool isValid(int x) {
    return (x % 2 != 0) && (x % 3 != 0) && (x % 5 != 0) && (x % 7 != 0);
}

int main() {
    long long n;
    if (!(std::cin >> n)) return 0;

    long long q = n / 210;
    int r = n % 210;

    int rem_count = 0;
    for (int i = 1; i <= r; ++i) {
        if (isValid(i)) {
            rem_count++;
        }
    }

    long long ans = q * 48 + rem_count;
    std::cout << ans << "\n";

    return 0;
}