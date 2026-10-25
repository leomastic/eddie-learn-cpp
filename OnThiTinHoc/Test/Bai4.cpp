#include <bits/stdc++.h>

int readIntInRange(std::string prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if(!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter again." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if(value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between "
                      << minValue << " and " << maxValue
                      << std::endl;
            continue;
        }

        return value;
    }
}

void calcAndPrintAns(int a, int b, int c) {
    int sastify = 0;
    int y_WillSastify = (c - (c % b)) / b;

    for(int i = 1; i <= y_WillSastify; i++) {
        int y = i;
        int x = (c - (b * y)) / a;

        if(std::gcd(x, y) == 1) {
            sastify++;
        }
    }

    std::cout << "There are " << sastify << " solutions that satisfy the conditions." << std::endl;
}

int main() {
    int a = readIntInRange("Please enter number a(1-->10^5): ", 1, 100000);
    int b = readIntInRange("Please enter number b(1-->10^5): ", 1, 100000);
    int c = readIntInRange("Please enter number c(1-->10^5): ", 1, 100000);

    calcAndPrintAns(a, b, c);

    return 0;
}