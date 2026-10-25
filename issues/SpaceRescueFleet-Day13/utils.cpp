#include "utils.h"

#include <iostream>

int readIntInRange(const std::string& prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
            continue;
        }

        return value;
    }
}
    
double readDoubleInRange(const std::string& prompt, double minValue, double maxValue) {
    double value;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Invalid value. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt << " (1 for yes, 0 for no): ";

        if (!(std::cin >> value)) {
            std::cout << "Invalid value. Please enter a valid value." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (value) {
            case 1:
                return true;

            case 0:
                return false;

            default:
                std::cout << "Please enter 1 or 0." << std::endl;
                break;
        }
    }
} 

std::string readNonEmptyWord(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::cin >> value;
        if (!value.empty()) {
            return value;
        }
        std::cout << "Value cannot be empty." << std::endl;
    }
}
