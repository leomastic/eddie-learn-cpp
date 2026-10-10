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
    if(isPrime(number)) return 1;

    int pow = 0;
    while(!checkOdd(number)) {
        number /= 2;
        ++pow;
        if(!checkOdd(number)) continue;
        break;
    }

    while(number % 3 == 0) {
        number /= 3;
        ++pow;
        if(number % 3 == 0) continue;
        break;
    }

    while(number % 5 == 0) {
        number /= 5;
        ++pow;
        if(number % 5 == 0) continue;
        break;
    }

    while(number % 7 == 0) {
        number /= 7;
        ++pow;
        if(number % 7 == 0) continue;
        break;
    }

    return pow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if(!(std::cin >> N)) return false;

    std::vector<int> num;
    for(int i = 0; i < N; ++i) {
        int a;
        if(!(std::cin >> a)) return false;
        num.push_back(a);
    }

    int k = 0;
    for(int i = 0; i < num.size(); ++i) {
        k = std::max(k, countPow(num[i]));
    }

    int sumPow = 0;
    for(int i = 0; i < num.size(); ++i) {
        sumPow += countPow(num[i]);
    }
    sumPow -= k;

    std::cout << sumPow << std::endl;

    return 0;
}