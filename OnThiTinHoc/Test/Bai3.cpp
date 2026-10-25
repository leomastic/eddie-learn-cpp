#include <bits/stdc++.h>

long long readLongLongInRange(std::string prompt, long long minValue, long long maxValue) {
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

std::string calcAndPrintAns(int M, int N, int K) {
    unsigned long long number = std::pow(M, N);

    std::string num_str = std::to_string(number);
    
    if (K >= num_str.length()) {
        return num_str;
    }
    
    if (K <= 0) {
        return "";
    }
    
    return num_str.substr(num_str.length() - K, K);
}

int main() {
    long long maxValue = 9223372036854775807;
    long long minValue = -9223372036854775807;

    long long M =
        readLongLongInRange("Please enter number M(-9,223,372,036,854,775,807 --> 9,223,372,036,854,775,807): "
                            , minValue, maxValue);
    long long N = readLongLongInRange("Please enter number N(0 --> 10^6): ", 0, 1000000);
    long long K = readLongLongInRange("Please enter number K(1 --> 9): ", minValue, maxValue);

    std::string result = calcAndPrintAns(M, N, K);
    std::cout << "The last " << K << " digits are: " << result << std::endl;

    return 0;
}