#include <bits/stdc++.h>

using namespace std;

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool contains(const vector<long long>& vec, long long val) {
    for (long long x : vec) {
        if (x == val) return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    vector<long long> foundPrimes;

    int len = s.length();
    for (int i = 0; i < len; ++i) {
        long long currentNum = 0;
        for (int j = i; j < len; ++j) {
            currentNum = currentNum * 10 + (s[j] - '0');
            
            if (isPrime(currentNum)) {
                if (!contains(foundPrimes, currentNum)) {
                    foundPrimes.push_back(currentNum);
                }
            }
        }
    }

    if (foundPrimes.empty()) {
        cout << "NO PRIMES" << endl;
    } else {
        cout << foundPrimes.size() << endl;
    }

    return 0;
}