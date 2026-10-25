#include <bits/stdc++.h>

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isHalfPrime(long long n) {
    if (n < 4) return false;

    int primeFactorCount = 0;
    long long temp = n;

    for (long long i = 2; i * i <= temp; ++i) {
        while (temp % i == 0) {
            if (!isPrime(i)) return false;
            primeFactorCount++;
            temp /= i;
        }
    }

    if (temp > 1) {
        if (!isPrime(temp)) return false;
        primeFactorCount++;
    }

    return primeFactorCount == 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;

    int numberOfHalfPrimes = 0;
    int largestHalfPrime = 0;

    for (int i = 1; i <= N; ++i) {
        if (isHalfPrime(i)) {
            ++numberOfHalfPrimes;
            largestHalfPrime = i;
        }
    }

    std::cout << numberOfHalfPrimes << " " << largestHalfPrime << "\n";

    return 0;
}