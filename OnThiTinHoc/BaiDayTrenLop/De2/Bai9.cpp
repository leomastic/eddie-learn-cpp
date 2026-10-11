#include <bits/stdc++.h>

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool checkOdd(int num) {
    return num % 2 != 0;
}

int countPow(int number) {
    int count = 0;
    for (int d = 2; d * d <= number; ++d) {
        while (number % d == 0) {
            number /= d;
            ++count;
        }
    }
    if (number > 1) {
        ++count;
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if(!(std::cin >> N)) return false;

    long long total = 0;
    int maximum = 0;
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        int count = countPow(x);
        total += count;
        if (count > maximum) maximum = count;
    }
    std::cout << total - maximum << '\n';

    return 0;
}