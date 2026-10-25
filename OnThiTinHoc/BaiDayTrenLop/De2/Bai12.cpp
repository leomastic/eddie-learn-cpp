#include <bits/stdc++.h>

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

long long reverseNum(long long num) {
    std::string stringNum = std::to_string(num);

    std::reverse(stringNum.begin(), stringNum.end());

    long long afterReverseNum = std::stoll(stringNum);

    return afterReverseNum;
}

bool checkIfGood(long long num) {
    return num == reverseNum(num);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long X;
    if(!(std::cin >> X)) return 0;

    long long count = 0;
    for(int i = 10; i <= X; ++i) {
        if(!checkIfGood(i)) continue;
        if(isPrime(reverseNum(i))) ++count;
    }

    std::cout << count << std::endl;

    return 0;
}