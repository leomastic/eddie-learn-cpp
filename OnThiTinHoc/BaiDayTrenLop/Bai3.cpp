#include <bits/stdc++.h>

long long calcSum(long long n) {
    long long sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isDualPrime(long long n) {
    if (!isPrime(n)) return false;
    long long sumDigit = calcSum(n);
    return isPrime(sumDigit);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long L, R;
    if (!(std::cin >> L >> R)) return 0;

    int total = 0; 

    for (long long i = L; i <= R; ++i) {
        if (isDualPrime(i)) {
            ++total;
        }
    }

    std::cout << total << "\n";

    return 0;
}