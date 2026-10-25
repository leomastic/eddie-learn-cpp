#include <bits/stdc++.h>

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int countPrimes(int number) {
    if(isPrime(number)) return 1;
    if(number == 1) return 0;
    

    int count = 0;
    for(int i = 2; i * i <= number; ++i) {
        if(number % i == 0) {
            while (number % i == 0) {
                number /= i;
            }
            ++count;
        }
    }

    if (number > 1) {
        ++count;
    }

    return count;
}

int countPrimesBetter(int a, int b, int k) {
    int count = 0;
    for(int i = a; i <= b; ++i) {
        if(countPrimes(i) >= k) ++count;
    }

    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q;
    if(!(std::cin >> q)) return 0;

    std::vector<int> a;
    std::vector<int> b;
    std::vector<int> k;
    for(int i = 0; i < q; ++i) {
        int a_i;
        int b_i;
        int k_i;

        if(!(std::cin >> a_i)) return 0;
        if(!(std::cin >> b_i)) return 0;
        if(!(std::cin >> k_i)) return 0;

        a.push_back(a_i);
        b.push_back(b_i);
        k.push_back(k_i);
    }

    for(int j = 0; j < q; ++j) {
        int count = countPrimesBetter(a[j], b[j], k[j]);

        std::cout << count << std::endl;
    }

    return 0;
}