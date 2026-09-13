#include "file_io.h"

#include <fstream>
#include <string>
#include <cctype>

// Validate that a text string represents a positive integer (allow leading/trailing whitespace)
static bool isPositiveIntegerText(const std::string& text) {
    if (text.empty()) { return false; }

    // Trim leading/trailing whitespace
    std::size_t start = 0;
    std::size_t end = text.size();
    while (start < end && std::isspace(static_cast<unsigned char>(text[start]))) { ++start; }
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1]))) { --end; }
    if (start == end) { return false; }

    for (std::size_t i = start; i < end; ++i) {
        char c = text[i];
        if (c < '0' || c > '9') { return false; }
    }
    return true;
}

bool saveMissions(const std::string& filename, const std::vector<Mission>& missions) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const Mission& m : missions) {
        file << m.getName() << "|" << m.getPriority() << "\n";
    }

    file.close();
    return true;
}

std::vector<Mission> loadMissions(const std::string& filename) {
    std::vector<Mission> missions;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return missions;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) { continue; }

        std::size_t sep = line.find('|');
        if (sep == std::string::npos) { continue; }

        std::string name = line.substr(0, sep);
        std::string priText = line.substr(sep + 1);

        if (!isPositiveIntegerText(priText)) { continue; }

        int pri = std::stoi(priText);

        if (name.empty() || pri < 1 || pri > 5) { continue; }

        missions.push_back(Mission(name, pri));
    }

    file.close();
    return missions;
}
