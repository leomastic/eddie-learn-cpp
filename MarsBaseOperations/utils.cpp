#include "utils.h"

#include <cctype>
#include <iostream>
#include <limits>
#include <string>

int readIntInRange(const std::string& prompt, int minValue, int maxValue) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minValue && value <= maxValue) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again." << std::endl;
    }
}

bool readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string answer;
        std::cin >> answer;
        if (answer == "y" || answer == "Y") {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if (answer == "n" || answer == "N") {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        std::cout << "Please answer yes or no." << std::endl;
    }
}

std::string readNonEmptyWord(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string value;
        std::getline(std::cin, value);
        if (value.empty()) {
            std::cout << "Name cannot be empty." << std::endl;
            continue;
        }

        bool hasWhitespace = false;
        for (char ch : value) {
            if (std::isspace(static_cast<unsigned char>(ch))) {
                hasWhitespace = true;
                break;
            }
        }

        if (!hasWhitespace) {
            return value;
        }

        std::cout << "Value cannot contain spaces." << std::endl;
    }
}

std::string readNonEmptyLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string value;
        std::getline(std::cin, value);
        if (!value.empty()) {
            bool allWhitespace = true;
            for (char ch : value) {
                if (!std::isspace(static_cast<unsigned char>(ch))) {
                    allWhitespace = false;
                    break;
                }
            }
            if (!allWhitespace) {
                return value;
            }
        }
        std::cout << "Value cannot be empty." << std::endl;
    }
}
