#include <bits/stdc++.h>

bool isValidBinary(std::string s) {
    if (s.length() == 0 || s.length() > 200) return false;
    for (char c : s) {
        if (c != '0' && c != '1') return false;
    }
    return true;
}

std::string readBinaryString(std::string prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && isValidBinary(value)) {
            return value;
        }
        std::cout << "Invalid value. Please enter again." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

std::string convertBinaryToOctal(std::string s) {
    while (s.length() % 3 != 0) {
        s = "0" + s;
    }

    std::string result = "";
    for (int i = 0; i < s.length(); i += 3) {
        int val = (s[i] - '0') * 4 + (s[i + 1] - '0') * 2 + (s[i + 2] - '0') * 1;
        result += std::to_string(val);
    }
    return result;
}

int main() {
    std::string binaryStr = readBinaryString("Enter binary string S: ");
    std::string octalStr = convertBinaryToOctal(binaryStr);

    std::cout << "Converted Octal Value: " << octalStr << std::endl;

    return 0;
}