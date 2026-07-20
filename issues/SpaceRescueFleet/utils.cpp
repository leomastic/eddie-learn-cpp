#include "utils.h"

#include <iostream>
#include <sstream>

static std::string trimString(const std::string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

int readIntInRange(
    const std::string& prompt,
    int minValue,
    int maxValue
) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimString(line);

        if (trimmed.empty()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        std::istringstream stream(trimmed);
        int value;
        char extra;
        if (!(stream >> value) || (stream >> extra)) {
            std::cout << "Invalid input. Please enter a whole number." << std::endl;
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Please enter a value between " << minValue
                      << " and " << maxValue << "." << std::endl;
            continue;
        }

        return value;
    }
}

double readDoubleInRange(
    const std::string& prompt,
    double minValue,
    double maxValue
) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimString(line);

        if (trimmed.empty()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }

        std::istringstream stream(trimmed);
        double value;
        char extra;
        if (!(stream >> value) || (stream >> extra)) {
            std::cout << "Invalid input. Please enter a decimal number." << std::endl;
            continue;
        }

        if (value < minValue || value > maxValue) {
            std::cout << "Please enter a value between " << minValue
                      << " and " << maxValue << "." << std::endl;
            continue;
        }

        return value;
    }
}

bool readYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimString(line);

        if (trimmed.empty()) {
            std::cout << "Please answer yes or no." << std::endl;
            continue;
        }

        for (char& c : trimmed) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }

        if (trimmed == "y" || trimmed == "yes") {
            return true;
        }

        if (trimmed == "n" || trimmed == "no") {
            return false;
        }

        std::cout << "Please answer yes or no." << std::endl;
    }
}

std::string readNonEmptyWord(
    const std::string& prompt
) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimString(line);

        if (trimmed.empty()) {
            std::cout << "Input cannot be empty." << std::endl;
            continue;
        }

        bool hasSpaces = false;
        for (char c : trimmed) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                hasSpaces = true;
                break;
            }
        }

        if (hasSpaces) {
            std::cout << "Please enter a single word without spaces." << std::endl;
            continue;
        }

        return trimmed;
    }
}
