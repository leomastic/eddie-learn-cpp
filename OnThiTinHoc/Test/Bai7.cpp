#include <bits/stdc++.h>

long long readLongLongInRange(std::string prompt, long long minValue, long long maxValue) {
    long long value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter again." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue
                      << std::endl;
            continue;
        }

        return value;
    }
}

bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; (long long)i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}

bool isValid(int x) {
    if (x == 1) return true;
    if (x <= 4) return false;
    return !isPrime(x);
}

int main() {
    int n = readLongLongInRange("Enter the total number of elements (n): ", 1, 100000);

    int count = 0;
    for (int i = 0; i < n; ++i) {
        std::string prompt = "Enter element a[" + std::to_string(i + 1) + "]: ";
        int a = readLongLongInRange(prompt, 1, 1000000000);

        if (isValid(a)) {
            count++;
        }
    }

    std::cout << "Number of elements satisfying the condition: " << count << std::endl;

    return 0;
}