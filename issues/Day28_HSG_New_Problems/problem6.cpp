#include <algorithm>
#include <iostream>

long long primeExponentInFactorial(long long n, long long prime) {
    long long exponent = 0;
    while (n > 0) {
        n /= prime;
        exponent += n;
    }
    return exponent;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    int base;
    if (!(std::cin >> n >> base)) return 0;

    long long answer = n;
    int remaining = base;

    for (int prime = 2; prime <= remaining / prime; ++prime) {
        if (remaining % prime != 0) continue;

        int baseExponent = 0;
        do {
            remaining /= prime;
            ++baseExponent;
        } while (remaining % prime == 0);

        answer = std::min(
            answer, primeExponentInFactorial(n, prime) / baseExponent);
    }

    if (remaining > 1) {
        answer = std::min(answer, primeExponentInFactorial(n, remaining));
    }

    std::cout << answer << '\n';
    return 0;
}