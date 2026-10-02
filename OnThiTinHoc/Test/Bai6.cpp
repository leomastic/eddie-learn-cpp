#include <bits/stdc++.h>

bool isValidOctal(const std::string& s) {
    if (s.empty() || s.length() > 100) return false;
    for (char c : s) {
        if (c < '0' || c > '7') return false;
    }
    return true;
}

std::string readOctalString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && isValidOctal(value)) {
            return value;
        }
        std::cout << "Invalid value. Please enter again." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

std::string addOctal(std::string a, std::string b) {
    std::string result = "";
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? (a[i] - '0') : 0;
        int digitB = (j >= 0) ? (b[j] - '0') : 0;

        int sum = digitA + digitB + carry;
        carry = sum / 8;
        result += std::to_string(sum % 8);

        i--;
        j--;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string a = readOctalString("Enter octal number a: ");
    std::string b = readOctalString("Enter octal number b: ");

    std::string sum = addOctal(a, b);

    std::cout << "Converted Octal Value: " << sum << std::endl;

    return 0;
}