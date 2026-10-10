#include <bits/stdc++.h>

long long calcSum(long long n) {
    long long sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    if (!(std::cin >> T) || T > 100) return 0;

    std::vector<long long> n(T);
    for (int i = 0; i < T; ++i) {
        std::cin >> n[i];
    }

    for (int i = 0; i < T; ++i) {
        std::cout << calcSum(n[i]) << "\n";
    }

    return 0;
}