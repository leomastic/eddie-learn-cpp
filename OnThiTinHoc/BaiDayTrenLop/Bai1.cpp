#include <bits/stdc++.h>

long long sumOfDivisors(long long n) {
    long long sum = 0;
    
    for (long long j = 1; j * j <= n; ++j) {
        if (n % j == 0) {
            sum += j;
            
            if (j * j != n) {
                sum += n / j;
            }
        }
    }
    
    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    if (!(std::cin >> T) || T > 100) return 0;

    for (int i = 0; i < T; ++i) {
        long long A;
        std::cin >> A;
        std::cout << sumOfDivisors(A) << "\n";
    }

    return 0;
}